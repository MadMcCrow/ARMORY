/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin.h" // header

#include "world_module.h"
#include "world_cell.h"

using namespace armory;


void WorldEditorPlugin::edit(Object *p_object) 
{

	/*
	AudioStream *s = Object::cast_to<AudioStream>(p_object);
	if (!s) {
		return;
	}

	audio_editor->edit(Ref<AudioStream>(s));
	*/
}

bool WorldEditorPlugin::handles(Object *p_object) const 
{
	return p_object->is_class("Module");
}

void WorldEditorPlugin::make_visible(bool p_visible) 
{
	//audio_editor->set_visible(p_visible);
}

WorldEditorPlugin::WorldEditorPlugin(EditorNode *p_node) 
{
	editor = p_node;
	//audio_editor = memnew(AudioStreamEditor);
	//add_control_to_container(CONTAINER_PROPERTY_EDITOR_BOTTOM, audio_editor);
	//audio_editor->hide();
}

WorldEditorPlugin::~WorldEditorPlugin() 
{
	// maybe delete editor
}



#endif // TOOLS_ENABLED
