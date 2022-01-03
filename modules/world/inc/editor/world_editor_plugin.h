/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_EDITOR_PLUGIN_CLASS_H
#define ARMORY_WORLD_EDITOR_PLUGIN_CLASS_H

#if TOOLS_ENABLED

#include <editor/editor_node.h>
#include <editor/editor_plugin.h>

namespace armory
{

class WorldEditorPlugin : public EditorPlugin
{
	GDCLASS(WorldEditorPlugin, EditorPlugin);

	EditorNode *editor;

public:
	virtual String get_name() const override { return "Armory World"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	WorldEditorPlugin(EditorNode *p_node);
	~WorldEditorPlugin();
};
};

#endif //TOOLS_ENABLED
#endif // ARMORY_WORLD_EDITOR_PLUGIN_CLASS_H
