/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H
#define ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H

#if TOOLS_ENABLED

// godot class
#include <scene/gui/panel_container.h>

// in godot namespace
class TabContainer;

namespace armory
{

// forward declaration :
class WorldResource;
class WorldEditorPluginCell;
class WorldEditorPluginModule;

/**
 * 	@class WorldEditorPluginWindow
 *	"window" that contains the buttons etc to edit world resources
 */
class WorldEditorPluginWindow : public  PanelContainer
{
	GDCLASS(WorldEditorPluginWindow, PanelContainer);

public: 

	/**
	 * 	Edit said world resource :
	 */
	void edit(const Ref<WorldResource> &Res);

	WorldEditorPluginWindow();
	~WorldEditorPluginWindow();

private:

	TabContainer* 				tab_container;
	WorldEditorPluginCell* 		cell_editor;
	WorldEditorPluginModule* 	module_editor;

};
};


#endif //TOOLS_ENABLED
#endif // ARMORY_WORLD_EDITOR_PLUGIN_WINDOW_CLASS_H
