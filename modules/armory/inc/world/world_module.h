/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_MODULE_CLASS_H
#define WORLD_MODULE_CLASS_H
 
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include "world_cell.h"

// we must use this namespace if we want to compile against godot
using namespace godot;

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
