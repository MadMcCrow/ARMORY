/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#include "register_types.h"

// we are tool only here !
#ifdef TOOLS_ENABLED
#include "world/world_plugin.h"

void register_armory_tools_types() 
{
	ClassDB::register_class<armory::WorldPlugin>();
}

void unregister_armory_tools_types() 
{
}

#endif //TOOLS_ENABLED
