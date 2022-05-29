/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_tile_set.h"
#include "world_tile.h"

using namespace armory;


void WorldTileSet::_bind_methods()
{
    // WorldTile Methods
    ClassDB::bind_method(D_METHOD("get_tiles"),   &WorldTileSet::get_tiles);
    ClassDB::bind_method(D_METHOD("set_tiles", "in_tiles"), &WorldTileSet::set_tiles);
	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY,   "tiles", PROPERTY_HINT_ARRAY_TYPE, "WorldTile"),   "set_tiles", "get_tiles");
}

Array WorldTileSet::get_tiles() const
{
    Array retval;
    const auto num = tiles.size();
    if (retval.resize(num) == Error::OK)
    {
        #pragma omp parallel for
        for (int idx = 0; idx < num; ++idx)
        {
            retval[idx] = tiles[idx];
        }
    }
    return retval;
}

void WorldTileSet::set_tiles(const Array& in_tiles)
{
    const size_t num = in_tiles.size();
    tiles.resize(num, Ref<WorldTile>());
    #pragma omp parallel for
    for (size_t idx = 0; idx < num; ++idx)
    {
        tiles[idx] = in_tiles[idx];
    }
}