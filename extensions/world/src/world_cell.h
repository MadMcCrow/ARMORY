/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CELL_CLASS_H
#define WORLD_CELL_CLASS_H


#include <cstdint> 
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/classes/object.hpp>


// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace world
{


/**
 *  @class Cell
 *  Describe a world cell with all the necessary info layed on top
 */
class WorldCell :  public Object
{
    GDCLASS(WorldCell, Object);
    static void _bind_methods();

public:

    /** how to represent it on the map */
    enum class Type : uint8_t
    {
        deep_sea     = 0,   // sea visual only
        sea_oil      = 1,   // on deep sea, spawns a offshore platform building
        sea          = 2,   // sea visual only
        shoreline    = 3,   // sea visual only
        beach        = 4,   // sea transition, allows unloading
        cliff        = 5,   // sea transition
        plain        = 6,   // level 0
        mound        = 7,   // level 1
        river        = 8,   // spawns on level 1 goes to sea
        hill         = 9,   // level 2
        hill_tree    = 10,  // prevents building, stops vehicules
        hill_rock    = 11,  // prevents building, does not stop tanks 
        ore_mine     = 12,  // on hills, spawns a ore mine building
        mountain     = 13,  // blocks land unit
        mountain_top = 14   // blocks planes
    };

private:
    Type T; 

    // TODO : bind enum, CTR, and use in world

};

}; // namespace world

#endif // ! WORLD_CELL_CLASS_H
