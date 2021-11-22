/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#include "register_types.h"

// world
#include "world/world.h"
#include "world/world_cell.h"
#include "world/world_module.h"
#include "world/world_statics.h"


#ifdef TOOLS_ENABLED
#endif //TOOLS_ENABLED

// statics holds enums, names, functions, etc for world
static armory::WorldStatics* world_statics = nullptr;

void register_armory_types() 
{
    ClassDB::register_class<armory::World>();
	ClassDB::register_class<armory::WorldCell>();
	ClassDB::register_class<armory::WorldModule>();

	ClassDB::register_class<armory::WorldStatics>();
	world_statics = memnew(armory::WorldStatics);
  	Engine::get_singleton()->add_singleton(Engine::Singleton("WorldStatics", armory::WorldStatics::get_singleton()));
}

void unregister_armory_types() 
{
	  memdelete(world_statics);
}

