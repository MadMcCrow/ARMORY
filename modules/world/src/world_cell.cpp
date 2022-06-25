/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_cell.h"

using namespace armory;

WorldCell::WorldCell(size_t bitset_size) 
{
    size_t padding = WORLD_MAX_TILE_SET - bitset_size;
    bit_tile_set.set();
    bit_tile_set >>= padding;
}

String WorldCell::to_string() const
{
    return String(bit_tile_set.to_string().c_str());
}