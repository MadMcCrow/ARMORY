/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_TILE_SET_H
#define WORLD_TILE_SET_H

// world
#include "world_inc.h"
#include "world_tile.h"

// make sure we do not override
namespace armory
{

/**
 * 	@class WorldTileSet
 *	Contains a list of tiles. saving this as a resource helps setting up scenes and game mode variations
 */
class WorldTileSet :  public Resource
{
    GDCLASS(WorldTileSet, Resource);
    static void _bind_methods();

public:

    // default CTR
    WorldTileSet() 
    : Resource()
    {}

private:

    /** list of tiles in the tile set */
    std::vector<Ref<WorldTile>> tiles;

    WorldTile::TileableShapes shape; 

public:

    /**
     * @brief Fill the set with rotated versions of tiles
     * @return a copy of self if duplicate, itelf otherwise
     */
    void fill_set(bool duplicate); 


    // function for the CPP system
    _ALWAYS_INLINE_ const std::vector<Ref<WorldTile>>& get_tile_set() const {return tiles; }

    //<GDScript interface>

    /** getter for @see tiles */
    Array get_tiles() const;

    /** setter for @see tiles */
    void set_tiles(const Array& in_tiles);

    //<\GDScript interface>
};
}; // namespace armory

#endif // ! WORLD_TILE_SET_H
