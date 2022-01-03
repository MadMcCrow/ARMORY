/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#include "register_types.h"

// world
#include "world.h"
#include "world_cell.h"
#include "world_module.h"
#include "world_statics.h"

#if TOOLS_ENABLED
#include "editor/world_module_preview_plugin.h"
#include "editor/world_editor_plugin.h"
#endif //TOOLS_ENABLED

// statics holds enums, names, functions, etc for world
static armory::WorldStatics* world_statics = nullptr;


#if TOOLS_ENABLED
static armory::ModulePreviewPlugin* ModulePreview = nullptr;
#endif // TOOLS_ENABLED

void register_world_types() 
{
    ClassDB::register_class<armory::World>();
	ClassDB::register_class<armory::Cell>();
	ClassDB::register_class<armory::Module>();
	ClassDB::register_class<armory::WorldStatics>();
#if TOOLS_ENABLED
	//ClassDB::register_class<armory::ModulePreviewPlugin>();
	EditorPlugins::add_by_type<armory::WorldEditorPlugin>();
	ModulePreview = memnew(armory::ModulePreviewPlugin);
	EditorResourcePreview::get_singleton()->add_preview_generator(Ref<armory::ModulePreviewPlugin>(ModulePreview));
#endif // TOOLS_ENABLED

	// create world statics singleton
	world_statics = memnew(armory::WorldStatics);
  	Engine::get_singleton()->add_singleton(Engine::Singleton("WorldStatics", armory::WorldStatics::get_singleton()));

}

void unregister_world_types() 
{
	// delete world statics singleton
	memdelete(world_statics);

#if TOOLS_ENABLED
	memdelete(ModulePreview);
#endif // TOOLS_ENABLED
}

