/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin_window.h"

#include <scene/gui/tab_container.h>

#include "editor/world_editor_plugin_cell.h"
#include "editor/world_editor_plugin_module.h"

#include "world_module.h"
#include "world_cell.h"

using namespace armory;

void WorldEditorPluginWindow::edit(const Ref<WorldResource> &Res)
{
    if (!tab_container)
        return;
    
    WorldResource* res_ptr = const_cast<WorldResource*>(Res.ptr());

	Module *mod = Object::cast_to<Module>(res_ptr);
	if (mod && module_editor) {
		module_editor->edit(Ref<Module>(mod));
        tab_container->set_current_tab(module_editor->get_index());
        return;
	}

    Cell *cell = Object::cast_to<Cell>(res_ptr);
    if (cell && cell_editor) {
		cell_editor->edit(Ref<Cell>(cell));
        tab_container->set_current_tab(cell_editor->get_index());
        return;
	}
}


WorldEditorPluginWindow::WorldEditorPluginWindow() : PanelContainer()
{

    tab_container = memnew(TabContainer);
	tab_container->set_tab_alignment(TabContainer::ALIGNMENT_LEFT);
	tab_container->set_use_hidden_tabs_for_min_size(true);
	tab_container->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	//tab_container->connect("tab_selected", callable_mp(this, &InputEventConfigurationDialog::_tab_selected));
	add_child(tab_container);

    cell_editor     = memnew(WorldEditorPluginCell);
    module_editor   = memnew(WorldEditorPluginModule);

    tab_container->add_child(module_editor);
    tab_container->add_child(cell_editor);
}

WorldEditorPluginWindow::~WorldEditorPluginWindow()
{
}


#endif // TOOLS_ENABLED
