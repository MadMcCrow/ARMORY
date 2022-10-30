/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_SOLVER_H
#define WORLD_SOLVER_H

#include "world_inc.h"
#include "world_tile.h"
#include "world_map.h"

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

    void set_owning_map(class WorldMap* in_world_map);

private:

    /** the generated tile_set for generation */
	std::vector<Ref<WorldTile>> gen_tile_set;

    /** total weight of gen_tile_set */
    float total_weight;

    /** map used as reference */
    Ref<WorldMap> owning_map;

    // current solver coordinate
    Vector3i Coord;

public:

     //<GDScript interface>


     //<\GDScript interface>

private:



};

}; // namespace armory

#endif // ! WORLD_SOLVER_H
