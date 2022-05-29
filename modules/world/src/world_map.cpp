/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_map.h"
#include "world_cell.h"
#include "world_tile.h"


using namespace armory;

// for error return
static WorldCell error_Cell = WorldCell(0);

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
    ClassDB::bind_method(D_METHOD("export_to_image", "out_image", "tile_size"),  &WorldMap::export_to_image);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "size"), "set_size", "get_size");
    ADD_PROPERTY(PropertyInfo(Variant::INT,      "seed"), "set_seed", "get_seed");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,   "tile_set_resource",  PROPERTY_HINT_RESOURCE_TYPE, "WorldTileSet"), "set_tile_set", "get_tile_set");
}

WorldMap::WorldMap() : Node()
{
}

TypedArray<String> WorldMap::get_configuration_warnings() const
{
    // for now no added errors
    return Node::get_configuration_warnings();
}


void WorldMap::init_cells()
{
    WARN_PRINT_ED("Cell Initialisation");
    // TODO : emit signal
    cell_vector.clear();
    cell_vector.resize( size.x * size.y, WorldCell(gen_tile_set.size())); 
}

void WorldMap::generate_cells()
{
    WARN_PRINT_ED("Generate Cell");
    // TODO : make every step async and emit signals
    generate_tile_set();
    init_cells();
    set_rand_seed(seed);
   
    while (!is_collapsed())
    {
        iterate_wfc();
    }
}

void WorldMap::generate_tile_set()
{
    WARN_PRINT_ED("Tile set initialisation");
    // TODO : emit signal

    gen_tile_set.clear();
    total_weight = 0.f;
    if (tile_set_resource.is_null())
        return;

    auto& tile_set = tile_set_resource->get_tile_set();
    gen_tile_set.reserve(tile_set.size() *4);
    for (const auto &tile : tile_set)
    {
        if (tile.is_valid())
        {
            // copy each rotation (data*4)
            Ref<WorldTile> n,e,s,w;
            n = tile;
            w = n->rotate();
            s = w->rotate();
            e = s->rotate();
            gen_tile_set.insert(gen_tile_set.end(), { n, s, e, w });
            total_weight += tile->get_weight() * 4.f;
        }
    }
}

void WorldMap::iterate_wfc()
{
    WARN_PRINT_ED("WFC step");
    // TODO : emit signal

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
        collapse(low.x,low.y);
        propagate_change(low.x, low.y);
    }
}

void WorldMap::propagate_change(int x, int y)
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

        //currently modified cell :
        auto &cell = get_cell(x,y);
        bool removed = false;
        // every one uses the same number of bits
        const auto num = cell.get_tile_bitset().size();

        // for each bits in bitset
        for (unsigned i = 0; i < num; ++i)
        {
            // this serve has an early exit. we don't care if there's only one configuration that will fit or thousands
            bool has_valid_combination = false;
            // each bit correspond to a tile in the tileset : if true, it's compatible
            std::vector<bool>::reference tile_bit = cell.get_tile_bitset()[i];

            // early exit : we previously established this does not work
            if (!tile_bit)
                continue;

            // check every combinations with neighbours. if one combination is already valid : just continue
            #pragma omp parallel for collapse(4)
            for (unsigned l = 0; l < num; ++l)
            {
                for (unsigned r = 0; r < num; ++r)
                {
                    for (unsigned u = 0; u < num; ++u)
                    {
                        for (unsigned d = 0; d < num; ++d)
                        {
                            // quick get out of loop if one combination previously succeeded
                            if (has_valid_combination)
                                continue;
                            const std::vector<bool>::reference left_bit    = get_cell(left(x,y)  ).get_tile_bitset()[l];
                            const std::vector<bool>::reference right_bit   = get_cell(right(x,y) ).get_tile_bitset()[r];
                            const std::vector<bool>::reference up_bit      = get_cell(up(x,y)    ).get_tile_bitset()[u];
                            const std::vector<bool>::reference down_bit    = get_cell(down(x,y)  ).get_tile_bitset()[d];
                            // at least one of these bit are not valid, it can't count has a valid combination 
                            if (!left_bit || !right_bit || !up_bit || !down_bit)
                                continue;
                            bool compat = gen_tile_set[i]->is_compatible(gen_tile_set[l], gen_tile_set[r], gen_tile_set[u], gen_tile_set[d]);
                            // at least a compination worked
                            if (compat)
                            {
                                #pragma omp critical
                                {
                                    has_valid_combination = true;
                                }
                            }
                        }
                    }
                }
            }  
            // we failed to find a valid combination, we set that bit to false
            if (!has_valid_combination)
            {
                tile_bit = false;
                removed = true;
            }
        }
        // this cell was changed, update neighbours 
        if (removed)
        {
            modified.push(left (x,y));
            modified.push(right(x,y));
            modified.push(up   (x,y));
            modified.push(down (x,y));
        }   
    }
}

void WorldMap::collapse(int x, int y)
{
    float value = rand_float(0.f,1.f);
    const auto weights = get_cell_normalized_weights(x,y);
    // value must be between 0 and 1
    float sum = 0;
    for (int idx = 0; idx < weights.size(); idx++)
    {
        sum += weights[idx];
        if (sum < value)
            continue;
        else
        {
            auto& cell = get_cell(x,y);
            cell.get_tile_bitset().resize(cell.get_tile_bitset().size(), false); // set all to false
            cell.get_tile_bitset()[idx] = true;                        // set to true;
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
    auto normalized_weights = get_cell_normalized_weights(x,y);
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


std::vector<float> WorldMap::get_cell_normalized_weights(int x, int y) const
{
    std::vector<float> normalized_weights;
    normalized_weights.resize(gen_tile_set.size(), 0.f);
    float local_total_weight = total_weight;

    const auto& cell = get_cell(x,y);
    const auto& bitset = cell.get_tile_bitset();
    ERR_FAIL_COND_V_MSG(bitset.size() != gen_tile_set.size(),{}, "Cell has a a different amount of bits than world has tiles");

    #pragma omp parallel for
    for (int idx = 0; idx< gen_tile_set.size(); idx++)
    {
        if (gen_tile_set[idx].is_valid())
        {
            const float weight = gen_tile_set[idx]->get_weight();
            if (!bitset[idx])
            {
                // this one has to be removed from the total weight
                #pragma omp critical
                {
                    local_total_weight -= weight;
                }
            }
            else
            {
                normalized_weights[idx] = weight;
            }
        }
        // leave at 0
    }
    #pragma omp parallel for
    for (auto & weight: normalized_weights)
    {
        weight/=local_total_weight;
    }
    return normalized_weights;
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
