/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "register_types.h"
#include "map/grid_node.h"
#include "map/tile_manager.h"

void register_armory_types() 
{
  ClassDB::register_class<Armory::GridNode>();
  ClassDB::register_class<Armory::TileManager>();
}

void unregister_armory_types() 
{
}
