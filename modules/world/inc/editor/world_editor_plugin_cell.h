/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_EDITOR_PLUGIN_CELL_CLASS_H
#define ARMORY_WORLD_EDITOR_PLUGIN_CELL_CLASS_H

#if TOOLS_ENABLED

// godot class
#include <scene/gui/scroll_container.h>
#include <core/templates/list.h>


// godot forward declaration
class EditorInspector;
class EditorProperty;
class VBoxContainer;

namespace armory
{


// armory forward declaration :
class Cell;

/**
 * 	@class WorldEditorPluginCell
 *	editor for cells 
 */
class WorldEditorPluginCell : public  ScrollContainer
{
	GDCLASS(WorldEditorPluginCell, ScrollContainer);

public: 

	/**
	 * 	Edit said world resource :
	 */
	void edit(const Ref<Cell> &Res);

	WorldEditorPluginCell();
	~WorldEditorPluginCell();

	/** save all local changes to the resource */
	void apply_changes();

private:

	VBoxContainer* 			editor_container;
	List<EditorProperty*> 	property_editors; /** editors spawned by @see edit */


	Ref<Cell> current_cell;	/** set via @see edit */

};
};


#endif //TOOLS_ENABLED
#endif // ARMORY_WORLD_EDITOR_PLUGIN_CELL_CLASS_H
