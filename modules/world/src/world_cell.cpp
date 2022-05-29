/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_cell.h"

using namespace armory;

WorldCell::WorldCell(size_t bitset_size) 
{
    bit_tile_set.resize(bitset_size, true);
}

