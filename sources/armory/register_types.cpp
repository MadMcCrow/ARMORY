/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */



#include "map/grid_node.h"        // GridNode
#include "map/tile_mesh.h"        // tile mesh
#include "map/tile_manager.h"     // TileManager
#include "map/tile_collection.h"  // TileCollection

#include "register_types.h"



void register_armory_types() 
{
  ClassDB::register_class<Armory::GridNode>();
  ClassDB::register_class<Armory::TileManager>();
  ClassDB::register_class<Armory::TileCollection>();
  ClassDB::register_class<Armory::TileMesh>();
}

void unregister_armory_types() 
{
}
