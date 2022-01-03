/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H
#define ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H

#if TOOLS_ENABLED

// godot class
#include <scene/gui/box_container.h>

namespace armory
{


// forward declaration :
class WorldResource;

/**
 * 	@class WorldEditorPluginWindow
 *	"window" that contains the buttons etc to edit world resources
 */
class WorldEditorPluginWindow : public VBoxContainer 
{
	GDCLASS(WorldEditorPluginWindow, VBoxContainer);

public: 

	/**
	 * 	Edit said world resource :
	 */
	void edit(const Ref<WorldResource> &Res);


	
};
};


#endif //TOOLS_ENABLED
#endif // ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H
