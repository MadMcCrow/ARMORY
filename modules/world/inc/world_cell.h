/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CELL_H
#define WORLD_CELL_H


// world
#include "world_inc.h"


namespace armory
{

/**
 * 	@struct WorldCell
 *	a cell reference a tile and contain info about what's on it
 *  it's only valid within a @see WorldMap
 */
struct WorldCell
{

    /** bitset corresponding to the tile_set in the WorldMap. if t */
    std::vector<bool> bit_tile_set;

    // default CTR
    WorldCell();

    // WFC functions  
    _ALWAYS_INLINE_ size_t tile_set_count() const {return std::count(bit_tile_set.begin(), bit_tile_set.end(), true);} /** number of compatible cells */
    _ALWAYS_INLINE_ bool is_collapsed() const { return tile_set_count() == 1;}      /** reduced to one cell */
    _ALWAYS_INLINE_ bool is_error() const     { return tile_set_count() < 1;}       /** no more valid cells */
    std::vector<float> get_normalized_weights() const;  /** get the weight of all the tiles, but normalized. keep order and indices */
    float get_entropy() const;                          /** how close to one cell are we (collapsed is 0) */

    /**
     * @brief  remove incompabilities with neighbours
     * @param left_cell      neighbour cell (we then extract the collapsed tile or nothing)
     * @param right_cell        ==
     * @param up_cell           ==
     * @param down_cell         ==
     * @return true if made a change
     * @todo : make calculate the entropy and store it when editing tile set
     * @todo : rewrite this function
     */

    bool remove_incompatible_tiles(const WorldCell& left_cell, const WorldCell& right_cell, const WorldCell& up_cell, const WorldCell& down_cell);

    /**
     * @brief restrict tile set to only the final tile
     * @param value the random value to make our selection [0.f-1.f]
     */
    void collapse(float value);

};
}; // namespace armory

#endif // ! WORLD_CELL_H
