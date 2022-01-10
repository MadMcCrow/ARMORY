/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin.h"

#include <editor/editor_scale.h>

#include "editor/world_editor_plugin_base.h"

#include "world_resource.h"

using namespace armory;

void WorldEditorPlugin::edit(Object *p_object) 
{
	WorldResource *s = Object::cast_to<WorldResource>(p_object);
	if (!s) {
		return;
	}
	if (world_editor)
	{
		world_editor->edit(Ref<WorldResource>(s));
	}
}

bool WorldEditorPlugin::handles(Object *p_object) const 
{
	return p_object->is_class("WorldResource");
}

void WorldEditorPlugin::make_visible(bool p_visible) 
{
	if (p_visible) {
		//editor->hide_animation_player_editors();
		//editor->animation_panel_make_visible(true);
		button->show();
		editor->make_bottom_panel_item_visible(world_editor);
		//world_editor->update_custom_nodes();
		world_editor->set_process_input(true);
	} else {
		if (world_editor)
		{
			if (world_editor->is_visible_in_tree()) 
			{
				editor->hide_bottom_panel();
			}
			world_editor->set_process_input(false);
		}
		button->hide();
	}
}

WorldEditorPlugin::WorldEditorPlugin(EditorNode *p_node) 
{
	editor = p_node;
	world_editor = memnew(WorldEditorPluginBase);
	world_editor->set_custom_minimum_size(Size2(0, 300) * EDSCALE);
	button = editor->add_bottom_panel_item(TTR("WorldEditor"), world_editor);
	button->hide();
}

WorldEditorPlugin::~WorldEditorPlugin() 
{
	//other plugin editor do not call memdelete on their deletion. 
	//memdelete(world_editor);
}



#endif // TOOLS_ENABLED
#include "world_cell.h"
