/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#include "register_types.h"


#include "world/world.h"
#include "world/world_cell.h"
#include "world/world_module.h"

#ifdef TOOLS_ENABLED
#endif //TOOLS_ENABLED



void register_armory_types() 
{
    ClassDB::register_class<armory::World>();
	ClassDB::register_class<armory::WorldCell>();
	ClassDB::register_class<armory::WorldModule>();
}

void unregister_armory_types() 
{
}

