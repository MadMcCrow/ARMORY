/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_map.h"

// world
#include "world_inc.h"

// godot
#include <core/object/class_db.h>
#include <core/error/error_macros.h>
#include <core/math/color.h>


using namespace armory;
		
static WorldMap::Cell error_Cell = WorldMap::Cell::error;

void WorldMap::_bind_methods()
{
	// Methods.

    // WorldMap Methods
    ClassDB::bind_method(D_METHOD("set_seed", "in_seed"),  &WorldMap::set_seed);
    ClassDB::bind_method(D_METHOD("get_seed"),  &WorldMap::get_seed);
    ClassDB::bind_method(D_METHOD("set_size", "in_size"),  &WorldMap::set_size);
    ClassDB::bind_method(D_METHOD("get_size"),  &WorldMap::get_size);
    ClassDB::bind_method(D_METHOD("init_cells"), &WorldMap::init_cells);
    ClassDB::bind_method(D_METHOD("generate_cells"),  &WorldMap::generate_cells);
    ClassDB::bind_method(D_METHOD("export_to_image", "out_image"),  &WorldMap::export_to_image);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "size"), "set_size", "get_size");
    ADD_PROPERTY(PropertyInfo(Variant::INT,      "seed"), "set_seed", "get_seed");

}

WorldMap::WorldMap() : Node()
{
}

void WorldMap::init_cells()
{
    cell_vector.resize( size.x * size.y, Cell::min);
}

void WorldMap::generate_cells()
{
    // todo : do each step async :)
    init_cells();
    set_rand_seed(seed);
    generate_voronoi();
    clean_cells();
}

void WorldMap::clean_cells()
{
    // se simply perform a gaussian blur
    // with a matrix of size (max-min) (+1 if pair)
    // this should be constexpr
    static const int matrix_size = ceil((Cell::max - Cell::min)/2.0)/2;
    static float     factor      = (matrix_size * 2 + 1) * (matrix_size * 2 +1);
    // copy values
    std::vector<float> cell_values;
    cell_values.resize( size.x * size.y, 0.f);

    // get the blurred values
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            const auto index = get_index(x,y);
            const float value  = 0.f;
            for (int fy = - matrix_size; fy < matrix_size; ++fy)
            {
                for (int fx = - matrix_size; fx < matrix_size; ++fx)
                {
                    cell_values[index] += static_cast<int>(cell_vector[get_index(x + fx,y + fy)]) / factor;
                }
            }
    
        }
    }

    // apply calculated values
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            const auto index   = get_index(x,y);
            cell_vector[index] = static_cast<Cell>(ceil(cell_values[index]));
        }
    }



}



void WorldMap::generate_voronoi()
{
    using Attractor = std::tuple<Vector2i,WorldMap::Cell>;

    const auto dimension = abs(size.x*size.y);
    const size_t attractor_num = rand_int(dimension/16, dimension/8);
    std::vector<Attractor> attractors;
    // must be done in a linear (not parallel) fashion to allow mersene to generate valid numbers
    attractors.reserve(attractor_num);
    for (int i = 0; i < attractor_num; i++)
    {
        const auto x = rand_int(0,size.x);
        const auto y = rand_int(0,size.y);
        const auto cell = static_cast<Cell>(rand_int(Cell::min, Cell::max));
        attractors.emplace_back(Vector2i(x,y),cell);
    }

    // now we can do a brute force voronoi :
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            // Lambda for Comparing distance
            const auto compare_less_distance = [this, x, y](const Attractor& a, const  Attractor& b)
            {
                const auto a_coord = std::get<0>(a);
                const auto b_coord = std::get<0>(b);
                const float dist_a = distance(a_coord.x,a_coord.y, x, y);
                const float dist_b = distance(b_coord.x,b_coord.y, x, y);
                return dist_a < dist_b;
            };
            // find closest attractor:
            const auto find_closest = min_element(attractors.begin(), attractors.end(), compare_less_distance);

            // Cell is the value of the closest attractor :
            Cell value = std::get<1>(Attractor(*find_closest));
            set_cell(x,y,value);
        }
    }
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

const WorldMap::Cell& WorldMap::get_cell(size_t x, size_t y) const
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

WorldMap::Cell&  WorldMap::get_cell(size_t x, size_t y)
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

void WorldMap::set_cell(size_t x, size_t y, const WorldMap::Cell& in_cell)
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
            const float cell = static_cast<uint8_t>(get_cell(x,y) & 0x0f) * 1.f;
            constexpr float min = static_cast<uint8_t>(Cell::min & 0x0f) * 1.f;
            constexpr float max = static_cast<uint8_t>(Cell::max & 0x0f) * 1.f;
            float value = remap(cell, min , max, 0.f,1.f);
            Color col = Color::from_hsv(0.f, 0.f, value, 1.f);
            out_image->set_pixel(x,y,col);
        }
    }
}

