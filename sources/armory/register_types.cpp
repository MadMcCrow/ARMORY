/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */



#include "map/grid_node.h"        // GridNode
#include "map/tile_mesh.h"        // tile mesh
#include "map/tile_manager.h"     // TileManager
#include "map/tile_collection.h"  // TileCollection
#include "register_types.h"


#ifdef TOOLS_ENABLED
#include "editor/resource_importer_tile_mesh.h"
#endif //TOOLS_ENABLED



#ifdef TOOLS_ENABLED
template<typename Class>
void _register_armory_importer()
{
	Ref<Class> import;
	import.instance();
	ResourceFormatImporter::get_singleton()->add_importer(import);
}
#endif // TOOLS_ENABLED

void register_armory_types() 
{
  ClassDB::register_class<Armory::GridNode>();
  ClassDB::register_class<Armory::TileManager>();
  ClassDB::register_class<Armory::TileCollection>();
  ClassDB::register_class<Armory::TileMesh>();

#ifdef TOOLS_ENABLED
if (Engine::get_singleton()->is_editor_hint()) 
{
	_register_armory_importer<Armory::ResourceImporterTileMesh>();
}
#endif
}

void unregister_armory_types() 
{
}

