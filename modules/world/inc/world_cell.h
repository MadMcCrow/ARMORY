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

    // please use this CTR
    WorldCell(size_t bitset_size);

    // WFC functions  
    _ALWAYS_INLINE_ std::vector<bool>&       get_tile_bitset()       {return bit_tile_set;}
    _ALWAYS_INLINE_ const std::vector<bool>& get_tile_bitset() const {return bit_tile_set;}
    _ALWAYS_INLINE_ size_t tile_set_count() const {return std::count(bit_tile_set.begin(), bit_tile_set.end(), true);} /** number of compatible cells */
    _ALWAYS_INLINE_ bool is_collapsed() const { return tile_set_count() == 1;}      /** reduced to one cell */
    _ALWAYS_INLINE_ bool is_error() const     { return tile_set_count() < 1;}       /** no more valid cells */

};
}; // namespace armory

#endif // ! WORLD_CELL_H
