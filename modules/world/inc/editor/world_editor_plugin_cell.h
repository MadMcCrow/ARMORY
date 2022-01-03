/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_EDITOR_PLUGIN_CELL_CLASS_H
#define ARMORY_WORLD_EDITOR_PLUGIN_CELL_CLASS_H

#if TOOLS_ENABLED

// godot class
#include <scene/gui/panel_container.h>


// godot forward declaration
class EditorInspector;

namespace armory
{


// armory forward declaration :
class Cell;

/**
 * 	@class WorldEditorPluginWindow
 *	"window" that contains the buttons etc to edit world resources
 */
class WorldEditorPluginCell : public  PanelContainer
{
	GDCLASS(WorldEditorPluginCell, PanelContainer);

public: 

	/**
	 * 	Edit said world resource :
	 */
	void edit(const Ref<Cell> &Res);

	WorldEditorPluginCell();
	~WorldEditorPluginCell();

private:

	EditorInspector * cell_inspector;
};
};


#endif //TOOLS_ENABLED
#endif // ARMORY_WORLD_EDITOR_PLUGIN_CELL_CLASS_H
