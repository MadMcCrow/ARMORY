/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_cell.h"
#include "world_tile.h"

// godot
#include <core/object/class_db.h>

using namespace armory;
		

void WorldCell::_bind_methods()
{

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

void WorldCell::remove_incompatible_tiles(const Ref<WorldCell>& left_cell, const Ref<WorldCell>& right_cell, const Ref<WorldCell>& up_cell, const Ref<WorldCell>& down_cell)
{
    std::set<Ref<WorldTile>> new_tile_set;

     #pragma omp parallel for collapse(4)
    for (unsigned l = 0; l < left_cell->get_tile_set().size(); ++l)
    {
        for (unsigned r = 0; r < right_cell->get_tile_set().size(); ++r)
        {
            for (unsigned u = 0; u < up_cell->get_tile_set().size(); ++u)
            {
                for (unsigned d = 0; d < down_cell->get_tile_set().size(); ++d)
                {
                    auto left   = left_cell->get_tile_set()[l];
                    auto right  = right_cell->get_tile_set()[r];
                    auto up     = up_cell->get_tile_set()[u];
                    auto down   = down_cell->get_tile_set()[d];

                    auto local_tile_set = tile_set;

                    for (unsigned i=tile_set.size(); i-->0;)
                    {
                        const auto& tile = tile_set[i];
                        bool compat = false;
                        if (tile.is_valid())
                        {
                            bool compat = false;
                            compat |= tile->is_compatible(left,  right,  up,     down);
                            compat |= tile->is_compatible(up,    down,   right,  left);  // 90  degrees clockwise
                            compat |= tile->is_compatible(right, left,   down,   up);    // 180 degrees clockwise
                            compat |= tile->is_compatible(down,  up,     left,   right); // 270 degrees clockwise
                        }
                        // at least a compination worked
                        if (compat)
                        {
                            #pragma omp critical
                            {
                                new_tile_set.insert(tile);
                            }
                        }
                    }
                
                }
            }
        }
    }

    // copy back in tile_set
    tile_set.clear();
    std::copy(new_tile_set.begin(), new_tile_set.end(), std::back_inserter(tile_set));
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
            auto selected_tile = tile_set[idx];
            if (selected_tile.is_valid())
            {
                tile_set.clear();
                tile_set.push_back(selected_tile);
                break; // we're done !
            }
        }
    }
}

std::vector<float> WorldCell::get_normalized_weights() const
{
    std::vector<float> normalized_weights;
    float total_weight;

    // no parallel : make sure to keep indices and order
    for (const auto & tile: tile_set)
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


void WorldCell::set_tile_set(const std::vector<Ref<WorldTile>>& in_tile_set)
{

}