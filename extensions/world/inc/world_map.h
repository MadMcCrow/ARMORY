/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

// world
#include "world_inc.h"
#include "world_cell.h"
#include "world_tile_set.h"
#include "world_solver.h"

/** World is part of armory */
namespace armory {

/**
 * 	@class WorldMap
 *	Base Matrix functions
 *	Offers function for child classes
 */
class WorldMap :  public Node
{
    GDCLASS(WorldMap, Node);
    static void _bind_methods();

public:

    // default CTR
    WorldMap();
    // default CTR
    ~WorldMap();

private:

    /** Requested seed for the rand num generator */ 
    int seed;

    /** the size for the generation  (todo : split in size + height) */
    Vector3i size;

    /** the tile set to use for solving the map */
    Ref<WorldTileSet> tile_set_resource;

    /** the cells generated */
	std::vector<WorldCell> cell_vector;

    /** the object that will take care of solving the  */
    Ref<WorldSolver> map_solver;    


public:
    //<GDScript interface>
    /** setter for @see map_solver */
    void set_map_solver(const Ref<WorldSolver> &in_solver);
    /** getter for @see map_solver */
    Ref<WorldSolver> get_map_solver() const {return map_solver;}
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
};

}; // namespace armory
#endif // ! WORLD_CLASS_H
