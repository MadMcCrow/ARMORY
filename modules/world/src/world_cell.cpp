/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_cell.h"
#include "world_tile.h"
#include "world_map.h"


using namespace armory;
		


//helper function to retrieve the data from the WorldMap singleton 
const std::vector<Ref<WorldTile>>& get_tile_set()
{
    const auto* map = WorldMap::get_singleton();
    return map->get_tile_set();
}


WorldCell::WorldCell() 
{
    // get WorldMap singleton
    // set tile set 

}


float WorldCell::get_entropy() const
{
    // {\displaystyle \mathrm {H} (X)=-\sum _{i=1}^{n}{\mathrm {P} (x_{i})\log _{b}\mathrm {P} (x_{i})}}
    // Entropy = sum{i[0->n]}(Pxi *logb(Pxi))
    auto normalized_weights = get_normalized_weights();
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

bool WorldCell::remove_incompatible_tiles( const WorldCell& left_cell, const WorldCell& right_cell, const WorldCell& up_cell, const WorldCell& down_cell)
{
    bool removed = false;
    // every one uses the same number of bits
    const auto num = bit_tile_set.size();

    // for each bits in bitset
    for (unsigned i = 0; i < num; ++i)
    {
        bool has_valid_combination = false;
        std::vector<bool>::reference tile = bit_tile_set[i];
        if (!tile)
            continue;

        // check every combinations with neighbours. if one combination is valid : just continue
        #pragma omp parallel for collapse(4)
        for (unsigned l = 0; l < num; ++l)
        {
            for (unsigned r = 0; r < num; ++r)
            {
                for (unsigned u = 0; u < num; ++u)
                {
                    for (unsigned d = 0; d < num; ++d)
                    {
                        // quick get out of loop if one combination succeeded
                        if (has_valid_combination)
                            continue;
            
                        const auto& left    = left_cell.bit_tile_set[l];
                        const auto& right   = right_cell.bit_tile_set[r];
                        const auto& up      = up_cell.bit_tile_set[u];
                        const auto& down    = down_cell.bit_tile_set[d];
                        

                        if (!left || !right || !up || !down)
                            continue;

                        const std::vector<Ref<WorldTile>>& tile_set = get_tile_set();
                        bool compat =  tile_set[i]->is_compatible(tile_set[l], tile_set[r], tile_set[u], tile_set[d]);
                    
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

        // not successfully found a valid configuration for this tile : remove it from tileset
        if (!has_valid_combination)
        {
            tile = false;
            removed = true;
        }
    }
    return removed;// true if removed something
}


void WorldCell::collapse(float value)
{
    auto weights = get_normalized_weights();
    // value must be between 0 and 1
    float sum = 0;
    for (int idx = 0; idx < weights.size(); idx++)
    {
        sum += weights[idx];
        if (sum < value)
            continue;
        else
        {
            bit_tile_set.resize(bit_tile_set.size(), false); // set all to false
            bit_tile_set[idx] = true;                        // set to true;
        }
    }
}

std::vector<float> WorldCell::get_normalized_weights() const
{
    std::vector<float> normalized_weights;
    float total_weight;

    // no parallel : make sure to keep indices and order
    for (const auto & tile: get_tile_set())
    {
        if (tile.is_valid())
        {
            float weight = tile->get_weight();
            normalized_weights.push_back(weight);
            total_weight += weight;
        }
        else
        {
            normalized_weights.push_back(0.f);
        }
    }

    // we can parallel !
    #pragma omp parallel for
    for (auto & weight: normalized_weights)
    {
        weight/=total_weight;
    }

    return normalized_weights;
}

