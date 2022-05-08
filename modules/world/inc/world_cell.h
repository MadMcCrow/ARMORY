/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CELL_H
#define WORLD_CELL_H


// world
#include "world_inc.h"


// godot-cpp
#include "core/io/resource.h"
#include "core/object/ref_counted.h"

// we must use this namespace if we want to compile against godot
using namespace godot;


// make sure we do not override
namespace armory
{


//forward declaration:
class WorldTile;

/**
 * 	@class WorldCell
 *	a cell reference a tile and contain info about what's on it
 *  @todo maybe make it a node
 */
class WorldCell : public RefCounted
{
    GDCLASS(WorldCell, RefCounted);
    static void _bind_methods();


public:

    // default CTR
    WorldCell() 
    : RefCounted()
    {}

    const Ref<WorldTile>& get_collapsed_tile() const;

    // reduced to one cell
    bool is_collapsed() const {return tile_set.size() == 1;}

    // no more valid cells
    bool is_error() const {return tile_set.size() < 1;}

    // how close to one cell are we (collapsed is 0)
    float get_entropy() const;

    /**
     * @brief  remove incompabilities with neighbours
     * @param left_cell      neighbour cell (we then extract the collapsed tile or nothing)
     * @param right_cell        ==
     * @param up_cell           ==
     * @param down_cell         ==
     * @todo : make calculate the entropy and store it when editing tile set :)
     */
    void remove_incompatible_tiles(const Ref<WorldCell>& left_cell, const Ref<WorldCell>& right_cell, const Ref<WorldCell>& up_cell, const Ref<WorldCell>& down_cell);
    /**
     * @brief restrict tile set to only the final tile
     * @param value the random value to make our selection [0.f-1.f]
     */
    void collapse(float value);

    /**
     * @brief Set the tile set vector
     * @param in_tile_set 
     * @todo : make calculate the entropy and store it when editing tile set :)
     */
    void set_tile_set(const std::vector<Ref<WorldTile>>& in_tile_set);

    /** const getter */
    const std::vector<Ref<WorldTile>>& get_tile_set() const {return tile_set;}

private:

    /** possible tiles */
    std::vector<Ref<WorldTile>> tile_set;


    /** get the weight of all the tiles, but normalized. keep order and indices */
    std::vector<float> get_normalized_weights() const;

public:

    //<GDScript interface>
    //<\GDScript interface>
};
}; // namespace armory

#endif // ! WORLD_CELL_H
