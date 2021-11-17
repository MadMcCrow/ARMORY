/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_MODULE_CLASS_H
#define ARMORY_WORLD_MODULE_CLASS_H

// std
#include <vector>

// godot
#include "core/object/class_db.h"
#include "core/io/resource.h"

//armory
#include "world_cell.h"


namespace world
{

/**
 * 	@class WorldModule
 *	contains the definition of a WFC module
 */
class WorldModule :  public Resource
{
    GDCLASS(WorldModule, Resource);
    static void _bind_methods();

public:

private:

    /**
     * Types of modules allowed on directions : top, down, left and right 
     * @note :
     *          this is stored as a vector as you can force conditions 
     *          to be more than one cell
     */
    std::vector<WorldCell::Type> north;
    std::vector<WorldCell::Type> south;
    std::vector<WorldCell::Type> east;
    std::vector<WorldCell::Type> west;

};

};


#endif // ! WORLD_MODULE_CLASS_H
