/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_SOLVER_H
#define WORLD_SOLVER_H

#include "world_inc.h"
#include "world_tile_set.h"

/** World is part of armory */
namespace armory {

/**
 * 	@class WorldSolver
 *	Fills a WorldMap with actual data
 */
class WorldSolver :  public RefCounted
{
    GDCLASS(WorldSolver, RefCounted);
    static void _bind_methods(); // bind for editor

public:

    /** CTR */
    WorldSolver();

private:

    int seed;

    // the size for the generation
    Vector3i size;

    /** the generated tile_set for generation */
	std::vector<Ref<WorldTile>> gen_tile_set;

    /** total weight of gen_tile_set */
    float total_weight;

    /** the tile set to use for solving the map */
    Ref<WorldTileSet> tile_set_resource;

public:

     //<GDScript interface>
    
    /** setter for @see size */
    void set_size(const Vector3i& in_size) {size = in_size;}
    /** getter for @see size */
    const Vector3i& get_size() const {return size;}

    /** setter for @see tile_set_resource */
    void set_tile_set(const Ref<WorldTileSet>& in_tile_set) {tile_set_resource = in_tile_set;}
    /** getter for @see tile_set_resource */
    Ref<WorldTileSet> get_tile_set() const {return tile_set_resource;}

    /** setter for @see seed */
    void set_seed(int in_seed) {seed = in_seed;}
    /** getter for @see seed */
    int get_seed() const {return seed;}

     //<\GDScript interface>

private:

    // current solver coordinate
    Vector3i Coord;

};

}; // namespace armory

#endif // ! WORLD_SOLVER_H
