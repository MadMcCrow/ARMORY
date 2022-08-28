/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

// world
#include "world_inc.h"
#include "world_solver.h"
#include "world_cell.h"

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


private:

    /** size property (stored as a godot Vector3i directly) */
    Vector3i size;

    /** the cells generated */
	std::vector<WorldCell> cell_vector;

    /** the object that will take care of solving the  */
    Ref<WorldSolver> map_solver;    


public:
    //<GDScript interface>
    void set_map_solver(const Ref<WorldSolver> &in_solver) {map_solver = in_solver;}
    Ref<WorldSolver> get_map_solver() const {return map_solver;}
    //<\GDScript interface>
};

}; // namespace armory
#endif // ! WORLD_CLASS_H
