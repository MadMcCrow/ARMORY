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
        Ref<WorldTile> tile = in_tiles[idx];
        if (tile.is_valid() && tile->get_shape() == shape) {
            tiles[idx] = in_tiles[idx];
        }
    }
}

void WorldTileSet::fill_set(bool duplicate)
{
    Ref<WorldTileSet> set = duplicate ? this->duplicate(false) : this;
    std::vector<Ref<WorldTile>> new_tile_array;
    new_tile_array.reserve(tiles.size() * shape); // number of rotations == number of sides 
    for (int idx = 0; idx < tiles.size(); ++idx)
    {
        for (int side = 0; side < shape; ++side) {
            auto target = tiles[idx]->rotate(side);
            const int num = std::count(new_tile_array.cbegin(), new_tile_array.cend(), target);
            if (num <= 0)
                new_tile_array.push_back(target); 
        }
    }
    // replace with new array
    set->tiles.swap(new_tile_array);
}