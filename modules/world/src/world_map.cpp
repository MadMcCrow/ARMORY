/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_map.h"
#include "world_cell.h"
#include "world_tile.h"

// godot
#include <core/object/class_db.h>
#include <core/error/error_macros.h>
#include <core/math/color.h>


using namespace armory;

// for error return
static Ref<WorldCell> error_Cell = nullptr;


void WorldMap::_bind_methods()
{
	// Methods.

    // WorldMap Methods
    ClassDB::bind_method(D_METHOD("set_seed", "in_seed"),  &WorldMap::set_seed);
    ClassDB::bind_method(D_METHOD("get_seed"),  &WorldMap::get_seed);
    ClassDB::bind_method(D_METHOD("set_size", "in_size"),  &WorldMap::set_size);
    ClassDB::bind_method(D_METHOD("get_size"),  &WorldMap::get_size);
    ClassDB::bind_method(D_METHOD("set_tile_set", "in_tile_set"),  &WorldMap::set_tile_set);
    ClassDB::bind_method(D_METHOD("get_tile_set"),  &WorldMap::get_tile_set);
    ClassDB::bind_method(D_METHOD("init_cells"), &WorldMap::init_cells);
    ClassDB::bind_method(D_METHOD("generate_cells"),  &WorldMap::generate_cells);
    ClassDB::bind_method(D_METHOD("export_to_image", "out_image"),  &WorldMap::export_to_image);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "size"), "set_size", "get_size");
    ADD_PROPERTY(PropertyInfo(Variant::INT,      "seed"), "set_seed", "get_seed");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY,   "tile_set", PROPERTY_HINT_ARRAY_TYPE, "WorldTile"), "set_tile_set", "get_tile_set");
}

WorldMap::WorldMap() : Node()
{
}

void WorldMap::init_cells()
{
    cell_vector.resize( size.x * size.y, nullptr);

    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            const auto index = get_index(x,y);
            cell_vector[index].instantiate();
            if (cell_vector[index].is_valid())
            {
                cell_vector[index]->set_tile_set(tile_set);
            }
        }
    }
}

void WorldMap::generate_cells()
{
    init_cells();
    set_rand_seed(seed);
    while (!is_collapsed())
    {
        iterate_wfc();
    }
}


void WorldMap::iterate_wfc()
{
    // first pick a cell : either random or lower entropy
    auto low    = Vector2i(rand_int(0,size.x), rand_int(0, size.y));
    float low_e = get_cell_entropy(low.x, low.y);
    
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            auto e = get_cell_entropy(x,y);
            if (e < low_e)
            {
                #pragma omp critical
                {
                    // perform check again, other thread could have changed it
                    if (e < low_e)
                    {
                        low_e = e;
                        low.x = x;
                        low.y = y;
                    }
                }
            }
        }
    }

    // neighbouring cells
    auto left  = Vector2i(repeat(low.x -1, size.x), low.y);
    auto right = Vector2i(repeat(low.x +1, size.x), low.y);
    auto up    = Vector2i(low.x, repeat(low.y -1, size.y));
    auto down  = Vector2i(low.x, repeat(low.y +1, size.y));
    
}

/** is there a final valid solution ? */
bool WorldMap::is_collapsed() const
{
    volatile bool stop_flag=false;
    bool is_collapsed = true;
    #pragma omp parallel for collapse(2) shared(stop_flag)
    for (int y = 0; y < size.y; ++y) 
    {
        for (int x = 0; x < size.x; ++x) 
        {
            if(stop_flag) continue;
            // a cell is not collapsed
            auto cell = get_cell(x,y);
            if(cell.is_valid())
            {
                if (cell->is_collapsed())
                {
                    #pragma omp critical
                    {
                    is_collapsed = false;
                    }
                    stop_flag=true;
                }
            }
        }
    }
    return is_collapsed;
}


float WorldMap::get_cell_entropy(int x, int y) const
{
    const Ref<WorldCell>& xy_cell = get_cell(x,y);
    if (xy_cell.is_valid())
    {
        return xy_cell->get_entropy();
    }
    return 0; 
}

float WorldMap::distance(int ax, int ay, int bx, int by) const
{
    ax = repeat(ax, size.x);
    ay = repeat(ay, size.y);
    bx = repeat(bx, size.x);
    by = repeat(by, size.y);
    // manhattan distance ?
    return abs(bx-ax) + abs(by-ay);
}

size_t WorldMap::get_index(int x, int y) const
{
    // beware negative numbers
    return repeat(x, size.x) + repeat(y, size.y) * size.x;
}

const Ref<WorldCell>& WorldMap::get_cell(size_t x, size_t y) const
{
    try
    {
        return cell_vector.at(get_index(x,y));
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_V_MSG(error_Cell, "index is out_of_range");
    }

}

Ref<WorldCell>&   WorldMap::get_cell(size_t x, size_t y)
{
    try
    {
        return cell_vector.at(get_index(x,y));
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_V_MSG(error_Cell, "index is out_of_range");
    }
}

void WorldMap::set_cell(size_t x, size_t y, const Ref<WorldCell>& in_cell)
{
    try
    {
        cell_vector.at(get_index(x,y)) = in_cell;
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_MSG("index is out_of_range");
    }
}


void WorldMap::export_to_image(Ref<Image> out_image)
{
    if (out_image.is_null())
    {
        out_image.instantiate();
    }
    // set the image
    out_image->create( size.x, size.y, false, Image::FORMAT_L8);

    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y) 
    {
        for (int x = 0; x < size.x; ++x) 
        {
            /*
            const float cell = static_cast<uint8_t>(get_cell(x,y) & 0x0f) * 1.f;
            constexpr float min = static_cast<uint8_t>(Cell::min & 0x0f) * 1.f;
            constexpr float max = static_cast<uint8_t>(Cell::max & 0x0f) * 1.f;
            float value = remap(cell, min , max, 0.f,1.f);
            Color col = Color::from_hsv(0.f, 0.f, value, 1.f);
            out_image->set_pixel(x,y,col);
            */
        }
    }
}

Array WorldMap::get_tile_set() const
{
    Array ret_val;
    int count = tile_set.size();
    ret_val.resize(count);
    #pragma omp parrallel for
    for (int i = 0; i < count; ++i) 
    {
        ret_val[i] = tile_set.at(i);
    }
    return ret_val;
}

void WorldMap::set_tile_set(const Array& in_tile_set)
{
    tile_set.clear();
    int count = in_tile_set.size();
    tile_set.resize(count);
    #pragma omp parrallel for
    for (int i = 0; i < count; ++i) 
    {
        tile_set[i] = in_tile_set[i];
    }
}