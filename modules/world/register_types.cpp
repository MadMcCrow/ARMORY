/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// godot
#include "register_types.h"
#include "core/object/class_db.h"

// world map
#include "world_map.h"
#include "world_tile.h"
#include "world_tile_set.h"

void initialize_world_module(ModuleInitializationLevel p_level)
{
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) 
    {
      GDREGISTER_CLASS(armory::WorldMap);
      GDREGISTER_CLASS(armory::WorldTile);
      GDREGISTER_CLASS(armory::WorldTileSet);
	  }
    // make sure we have only one WorldMap.
    Engine::get_singleton()->add_singleton(Engine::Singleton("WorldMap", armory::WorldMap::get_singleton()));
}

void uninitialize_world_module(ModuleInitializationLevel p_level)
{
}

