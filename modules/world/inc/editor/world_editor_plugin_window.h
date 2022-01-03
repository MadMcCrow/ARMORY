/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H
#define ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H

#if TOOLS_ENABLED

// godot class
#include <editor/editor_resource_preview.h>

namespace armory
{
class WorldEditorPluginWindow : public VBoxContainer 
{
	GDCLASS(WorldEditorPluginWindow, VBoxContainer);
	
};
};


#endif //TOOLS_ENABLED
#endif // ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H
