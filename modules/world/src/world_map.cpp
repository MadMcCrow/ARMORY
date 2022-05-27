/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_map.h"
#include "world_cell.h"
#include "world_tile.h"

// godot
#include "core/config/project_settings.h"

using namespace armory;

// for error return
static WorldCell error_Cell = WorldCell();

// singleton ptr default value 
WorldMap *WorldMap::singleton = nullptr;

void add_custom_project_setting(String name, Variant default_value, Variant::Type type, const PropertyHint hint, String hint_string = "")
{
    auto PS = ProjectSettings::get_singleton();
    if (!PS)
    {
        ERR_FAIL_MSG("Failed to get project settings singleton, some module initialisation order error maybe !");
        return;
    }

	if (PS->has_setting(name))
        return;

	
	PropertyInfo setting_info(type, name, hint, hint_string);
  
	PS->set_setting(name, default_value);
	PS->set_custom_property_info(setting_info.name, setting_info);
	PS->set_initial_value(name, default_value);
    
	ERR_FAIL_COND_EDMSG(PS->save(), "Failed to save project settings");
}

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
    ClassDB::bind_method(D_METHOD("export_to_image", "out_image", "tile_size"),  &WorldMap::export_to_image);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "size"), "set_size", "get_size");
    ADD_PROPERTY(PropertyInfo(Variant::INT,      "seed"), "set_seed", "get_seed");

    add_custom_project_setting("WorldTileSet", Array(),  Variant::ARRAY, PROPERTY_HINT_ARRAY_TYPE, "WorldTile");
}

const std::vector<Ref<WorldTile>>& WorldMap::get_tile_set() const
{
    if (gen_tile_set.size() >0)
        return gen_tile_set;
    return tile_set;
}


WorldMap::WorldMap() : Node()
{
}

void WorldMap::init_cells()
{
    cell_vector.clear();
    cell_vector.resize( size.x * size.y, WorldCell()); 
}

void WorldMap::generate_cells()
{
    init_cells();
    set_rand_seed(seed);


    // for each element of tile_set, add new ones :)
    for (const auto &tile : tile_set)
    {
        // copy each rotation (data*4)
        Ref<WorldTile> n,e,s,w;
        n = tile;
        w = n->rotate();
        s = w->rotate();
        e = s->rotate();
        gen_tile_set.insert(gen_tile_set.end(), { n, s, e, w });
    }

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
            if (e < low_e && e > 0)
            {
                #pragma omp critical
                {
                    // perform check again, other thread could have changed low_e
                    // above zero cannot change
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

    // neighbouring cells (coord)
    auto left  = Vector2i(repeat(low.x -1, size.x), low.y);
    auto right = Vector2i(repeat(low.x +1, size.x), low.y);
    auto up    = Vector2i(low.x, repeat(low.y -1, size.y));
    auto down  = Vector2i(low.x, repeat(low.y +1, size.y));
    
    auto& cell       = get_cell(low.x, low.y);
    auto& left_cell  = get_cell(left.x, left.y);
    auto& right_cell = get_cell(right.x, right.y);
    auto& up_cell    = get_cell(up.x, up.y);
    auto& down_cell  = get_cell(down.x, down.y);
    if (!cell.is_collapsed() && !cell.is_error())
    {
        cell.remove_incompatible_tiles(left_cell, right_cell, up_cell, down_cell);
        cell.collapse(rand_float(0.f,1.f));
        propagate_change(low.x, low.y);
    }

}

bool WorldMap::propagate_change(int x, int y)
{
    const auto left  = [this](auto lx,auto ly){return Vector2i(repeat(lx -1, size.x), ly);};
    const auto right = [this](auto rx,auto ry){return Vector2i(repeat(rx +1, size.x), ry);};
    const auto up    = [this](auto ux,auto uy){return Vector2i(ux, repeat(uy -1, size.y));};
    const auto down  = [this](auto dx,auto dy){return Vector2i(dx, repeat(dy +1, size.y));};

    std::stack<Vector2i> modified; 

    modified.emplace(Vector2i(x,y));

    while (!modified.empty())
    {
        // cannot use tie with C-style array :(
        x = modified.top().coord[0];
        y = modified.top().coord[1];
        modified.pop();

        auto cell = get_cell(x,y);

        bool removed = cell.remove_incompatible_tiles(
            get_cell(left (x,y)),
            get_cell(right(x,y)),
            get_cell(up   (x,y)),
            get_cell(down (x,y)));

        if (removed)
        {
            modified.push(left (x,y));
            modified.push(right(x,y));
            modified.push(up   (x,y));
            modified.push(down (x,y));
        }
        
    }
    
    
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
            if (cell.is_collapsed())
            {
                #pragma omp critical
                {
                is_collapsed = false;
                }
                stop_flag=true;
            }
        }
    }
    return is_collapsed;
}


float WorldMap::get_cell_entropy(int x, int y) const
{
     // {\displaystyle \mathrm {H} (X)=-\sum _{i=1}^{n}{\mathrm {P} (x_{i})\log _{b}\mathrm {P} (x_{i})}}
    // Entropy = sum{i[0->n]}(Pxi *logb(Pxi))
    auto normalized_weights = get_cell(x,y).get_normalized_weights();
    float entropy = 0;
    #pragma omp parallel for
    for (auto & weight: normalized_weights)
    {
        float local_ent_sum = weight * faster_logf(weight);
        // section to make the sum
        #pragma omp critical
        {
            entropy+=local_ent_sum;
        }
    }
    return entropy;
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

size_t WorldMap::get_index(const int &x, const int &y) const
{
    // beware negative numbers
    return repeat(x, size.x) + repeat(y, size.y) * size.x;
}

const WorldCell& WorldMap::get_cell(const int &x, const int &y) const
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

WorldCell& WorldMap::get_cell(const int &x, const int &y)
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

void WorldMap::set_cell(const int &x, const int &y, const WorldCell& in_cell)
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


void WorldMap::export_to_image(Ref<Image> out_image, int tile_size)
{
    if (out_image.is_null())
    {
        out_image.instantiate();
    }

    
    // set the image
    out_image->create( size.x * tile_size, size.y *tile_size, false, Image::FORMAT_L8);

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
