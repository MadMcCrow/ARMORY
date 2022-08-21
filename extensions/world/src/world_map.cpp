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
    ClassDB::bind_method(D_METHOD("set_seed", "in_seed"), &WorldMap::set_seed);
    ClassDB::bind_method(D_METHOD("get_seed"), &WorldMap::get_seed);
    ClassDB::bind_method(D_METHOD("set_size", "in_size"), &WorldMap::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &WorldMap::get_size);
    ClassDB::bind_method(D_METHOD("set_tile_set", "in_tile_set"), &WorldMap::set_tile_set);
    ClassDB::bind_method(D_METHOD("get_tile_set"), &WorldMap::get_tile_set);
    ClassDB::bind_method(D_METHOD("init_cells"), &WorldMap::init_cells);
    ClassDB::bind_method(D_METHOD("generate_cells"), &WorldMap::generate_cells);
    ClassDB::bind_method(D_METHOD("export_to_image", "out_image", "tile_size"), &WorldMap::export_to_image);

    // Properties
    ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "size"), "set_size", "get_size");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tile_set_resource", PROPERTY_HINT_RESOURCE_TYPE, "WorldTileSet"), "set_tile_set", "get_tile_set");
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
    BENCHMARK_FUNC()
    // TODO : emit signal
    cell_vector.clear();
    const auto size_2d = size.x * size.y;
    const auto tile_count = gen_tile_set.size();
    // init cell vector :
    cell_vector.reserve(size_2d);
    for (int idx = 0; idx < size_2d; ++idx)
    {
        cell_vector.emplace_back(tile_count);
    }
    WARN_PRINT_ED("init cells : size is " + String(size) + " with " + itos(tile_count) + " tiles");
}

void WorldMap::generate_cells()
{
    WARN_PRINT_ED("generate cell ");

    // TODO : make every step async and emit signals
    generate_tile_set();
    init_cells();
    set_rand_seed(seed);
    auto start = std::chrono::system_clock::now();
    // costly operation:
    wfc_loop();
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    WARN_PRINT_ED("generate cell : generation took : " + itos(elapsed.count()) + "ms");

    // auto exit for now
    CRASH_NOW();
}

void WorldMap::wfc_loop()
{
    BENCHMARK_FUNC()

    std::stack<Vector2i> low_candidates;
    // first pick a cell : either random or lower entropy
    {
        auto start = Vector2i(rand_int(0, size.x - 1), rand_int(0, size.y - 1));
        low_candidates.emplace(start);
    }
     
    // TODO : replace while with function and separate thread 
    // WFC main loop :
    while (true)
    {
        //
        // WFC STEP : Find lowest entropy or finish
        //
        std::optional<Vector2i> lowest;
        {
            float lowest_e = 0.f;
            if (!low_candidates.empty())
            {
                // one of our candidates is the lowest entropy :
                while (!low_candidates.empty())
                {
                    Vector2i low = low_candidates.top();
                    low_candidates.pop();
                    auto low_e = get_cell_entropy(low.x, low.y);
                    if (!lowest && low_e > 0.f)
                    {
                        lowest = low;
                        lowest_e = low_e;
                    }
                    else
                    {
                        if (get_cell_entropy(low.x, low.y) < lowest_e)
                        {
                            lowest = low;
                        }
                    }
                }    
            }
            
            // either no low candidates, or all of those were collapsed already
            if (!lowest)
            {
                WARN_PRINT_ED("wfc loop : no candidates found");
                //#pragma omp parallel for collapse(2) shared(lowest_e)
                for (size_t x = 0; x < size.x; ++x)
                {
                    for (size_t y = 0; y < size.y; ++y)
                    {
                        auto cell_e = get_cell_entropy(x,y);
                        if (cell_e <= 0.f) // collapsed
                        {
                            continue;
                        }

                        if (!lowest || lowest_e > cell_e)
                        {
                            //#pragma omp critical
                            {
                                if (!lowest || lowest_e > cell_e)
                                {
                                    lowest = Vector2i(x,y);
                                    lowest_e = cell_e;
                                }
                            }
                        }
                    }
                }

                // did not find new low -> we are collapsed
                if (!lowest)
                {
                    WARN_PRINT_ED("wfc loop : all cells are collapsed");
                    break; // we're done !
                }
            }
        }
        
        // empty
        if (!low_candidates.empty())
        {
            auto empty_stack = std::stack<Vector2i>();
            low_candidates.swap(empty_stack);
        }

        //
        // WFC STEP : collapse lost entropy cell :
        //
        collapse_cell(lowest->x, lowest->y);

        //
        // WFC STEP : propagate change :
        //
        propagate_change(lowest->x, lowest->y, low_candidates);

        //
        // WFC STEP : get the low candidates in :
        //
        low_candidates.push(left(lowest->x, lowest->y));
        low_candidates.push(right(lowest->x, lowest->y));
        low_candidates.push(up(lowest->x, lowest->y));
        low_candidates.push(down(lowest->x, lowest->y));
    }
}

void WorldMap::generate_tile_set()
{
    // TODO : emit signal

    gen_tile_set.clear();
    total_weight = 0.f;
    if (tile_set_resource.is_null())
        return;

    auto &tile_set = tile_set_resource->get_tile_set();
    gen_tile_set.reserve(tile_set.size() * 4);
    for (const auto &tile : tile_set)
    {
        if (tile.is_valid())
        {
            // copy each rotation (data*4)
            Ref<WorldTile> n, e, s, w;
            n = tile;
            w = n->rotate();
            s = w->rotate();
            e = s->rotate();
            gen_tile_set.insert(gen_tile_set.end(), {n, s, e, w});
            total_weight += tile->get_weight() * 4.f;
        }
    }
    WARN_PRINT_ED("Tile set initialisation : " + itos(gen_tile_set.size()) + " tiles with a total weight of " + rtos(total_weight));
}

void WorldMap::propagate_change(int x, int y, std::stack<Vector2i> &changed)
{
    WARN_PRINT_ED("propagate_change : " + String(Vector2i(x,y)));
    std::stack<Vector2i> to_check;
    to_check.emplace(Vector2i(x, y));
    while (!to_check.empty())
    {
        const auto& coord = to_check.top();
        x = coord.x;
        y = coord.y;
        to_check.pop();

        // currently modified cell :
        auto &cell = get_cell(x, y);
        bool removed = false;
        // every one uses the same number of bits : the number of tile in tileset
        const auto num = gen_tile_set.size();

        // for each bits in bitset
        for (unsigned i = 0; i < num; ++i)
        {
            // early exit : we previously established this does not work
            if (cell.get_tile_bitset()[i] == false)
                continue;

            // this serve has an early exit. we don't care if there's only one configuration that will fit or thousands
            bool has_valid_combination = false;

            // check every combinations with neighbours. if one combination is already valid : just continue
            //#pragma omp parallel for collapse(4)
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

                            // all neighbours must be valid to be a valid combination
                            if (!(  get_cell(left(x, y)).is_valid(l)     &&
                                    get_cell(right(x, y)).is_valid(r)    &&
                                    get_cell(up(x, y)).is_valid(u)       &&
                                    get_cell(down(x, y)).is_valid(d)))
                            {
                                continue;
                            }

                            bool compat = gen_tile_set[i]->is_compatible(gen_tile_set[l], gen_tile_set[r], gen_tile_set[u], gen_tile_set[d]);
                            // at least a combination worked
                            if (compat)
                            {
                                //#pragma omp critical
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
                WARN_PRINT_ED("propagate_change : removed bit " + itos(i));
                cell.get_tile_bitset().reset(i);
                removed = true;
            }
        }
        // this cell was changed, update neighbours
        if (removed)
        {
            changed.push(coord);
            to_check.push(left(x, y));
            to_check.push(right(x, y));
            to_check.push(up(x, y));
            to_check.push(down(x, y));
        }
    }
}

void WorldMap::collapse_cell(int x, int y)
{
    float value = rand_float(0.f, total_weight);
    auto &cell = get_cell(x,y);
    const auto &bitset = cell.get_tile_bitset();
    // value must be between 0 and 1
    float sum = 0.f;
    int idx = 0;
    while (sum < value)
    {
        float weight = gen_tile_set[idx]->get_weight();
        if (!bitset[idx])
        {
            value -= weight;
        }
        else
        {
            sum += weight;
        }
        ++idx;
    }
    cell.collapse(idx);
}

float WorldMap::get_cell_entropy(int x, int y) const
{
    BENCHMARK_FUNC()
    // we could use shannon entropy, but using a function with similar variation (sign of derivative)
    // improves performance a lot.
    //
    // Shannon :
    // {\displaystyle \mathrm {H} (X)=-\sum _{i=1}^{n}{\mathrm {P} (x_{i})\log _{b}\mathrm {P} (x_{i})}}
    // Entropy = sum{i[0->n]}(Pxi *logb(Pxi))
    //
    // Ours :
    //  Entropy = sum{i[0->n]}(Pxi)
    //
    const auto &cell = get_cell(x,y);
    const auto &bitset = cell.get_tile_bitset();
    // collapsed :
    if (bitset.count() <= 1)
    {   
        return 0.f;
    }
    float entropy = 0.f;
    #pragma omp parallel for shared(entropy)
    for (int idx = 0; idx < gen_tile_set.size(); ++idx)
    {
            if (gen_tile_set[idx].is_valid())
            {
                const float weight = bitset.test(idx) ? gen_tile_set[idx]->get_weight() : 0.f;
                if (weight != 0)
                {
                    #pragma omp critical
                    {
                        entropy += weight;
                    }
                }
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
    return abs(bx - ax) + abs(by - ay);
}

size_t WorldMap::get_index(const int &x, const int &y) const
{
    // beware negative numbers
    return repeat(x, size.x) + repeat(y, size.y) * size.x;
}

const WorldCell &WorldMap::get_cell(const int &x, const int &y) const
{
    try
    {
        return cell_vector.at(get_index(x, y));
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_V_MSG(error_Cell, "index is out_of_range");
    }
}

WorldCell &WorldMap::get_cell(const int &x, const int &y)
{
    try
    {
        return cell_vector.at(get_index(x, y));
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_V_MSG(error_Cell, "index is out_of_range");
    }
}

void WorldMap::set_cell(const int &x, const int &y, const WorldCell &in_cell)
{
    try
    {
        cell_vector.at(get_index(x, y)) = in_cell;
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
    out_image->create(size.x * tile_size, size.y * tile_size, false, Image::FORMAT_L8);

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
