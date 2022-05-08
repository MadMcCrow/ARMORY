/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#include "register_types.h"

// world map
#include "world_map.h"
#include "world_tile.h"


void register_world_types() 
{
    ClassDB::register_class<armory::WorldMap>();
    ClassDB::register_class<armory::WorldTile>();
}

void unregister_world_types() 
{
}

