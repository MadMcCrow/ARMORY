/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_RESOURCE_CLASS_H
#define ARMORY_WORLD_RESOURCE_CLASS_H


// godot
//#include <core/object/class_db.h>
#include <core/io/resource.h>




namespace armory
{

/**
 * 	@class WorldResource
 *	base definition for all armory_world resources
 */
class WorldResource :  public Resource
{
    GDCLASS(WorldResource, Resource);
    static void _bind_methods();
};

};



#endif // ! ARMORY_WORLD_RESOURCE_CLASS_H
