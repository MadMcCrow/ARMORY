/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_MODULE_CLASS_H
#define ARMORY_WORLD_MODULE_CLASS_H

// std
#include <map>

// godot
#include "core/object/class_db.h"
#include "core/io/resource.h"

//armory
#include "world_cell.h"


namespace armory
{

/**
 * 	@class WorldModule
 *	contains the definition of a WFC module
 *  A module has a name (acting as a key), and a pattern.
 *  the pattern is a small subset of tiles
 */
class WorldModule :  public Resource
{
    GDCLASS(WorldModule, Resource);


    static void _bind_methods();


public:

    WorldModule();

private:

    /**
     *  a simple struct to store infos of the cells
     */
    struct ModuleCell
    {
        // Cell to use
        Ref<WorldCell> cell;
        
        // North facing rotation [North, South, East, West]
        int rotation;

    };

    /**
     * cells contained in this module
     */
    std::map<Vector2i, ModuleCell> cells;


protected: 


    /**
     *  setter and getter for modules
     *  we convert to array (of dict), but to avoid casting all the time, we store as std::vector of Struct
     */
    Array get_cells() const;
    void set_cells(const Array& in_modules);

};
        

};



#endif // ! WORLD_MODULE_CLASS_H
