/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin_base.h"

#include <scene/gui/tab_container.h>

#include "editor/world_editor_plugin_cell.h"
#include "editor/world_editor_plugin_module.h"

#include "world_module.h"
#include "world_cell.h"

using namespace armory;

void WorldEditorPluginBase::edit(const Ref<WorldResource> &Res)
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


WorldEditorPluginBase::WorldEditorPluginBase() : PanelContainer()
{

    tab_container = memnew(TabContainer);
	tab_container->set_tab_alignment(TabContainer::ALIGNMENT_LEFT);
	//tab_container->set_use_hidden_tabs_for_min_size(true);
	tab_container->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	//tab_container->connect("tab_selected", callable_mp(this, &InputEventConfigurationDialog::_tab_selected));
	add_child(tab_container);

    cell_editor = memnew(WorldEditorPluginCell);
    cell_editor->set_name(TTR("Cell"));
    cell_editor->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    cell_editor->set_h_size_flags(Control::SIZE_EXPAND_FILL);

    module_editor = memnew(WorldEditorPluginModule);
    module_editor->set_name(TTR("Module"));
    module_editor->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    module_editor->set_h_size_flags(Control::SIZE_EXPAND_FILL);

    tab_container->add_child(module_editor);
    tab_container->add_child(cell_editor);
}

void WorldEditorPluginBase::gui_input(const Ref<InputEvent> &p_event)
{
    PanelContainer::gui_input(p_event);
    if (p_event.is_valid())
    {
        if (p_event->is_action("ui_accept"))
        {
            input_validate();
        }
    }
}

void WorldEditorPluginBase::unhandled_key_input(const Ref<InputEvent> &p_event) 
{
    PanelContainer::unhandled_key_input(p_event);
    if (p_event.is_valid())
    {
        if (p_event->is_action("ui_accept"))
        {
            input_validate();
        }
    }
}


void WorldEditorPluginBase::input_validate()
{
    if (tab_container)
    {
        auto active_node = tab_container->get_child(tab_container->get_current_tab());
        if (auto cell_ed = Object::cast_to<WorldEditorPluginCell>(active_node))
        {
            cell_ed->apply_changes();
        }
    }
}


WorldEditorPluginBase::~WorldEditorPluginBase()
{
}


#endif // TOOLS_ENABLED
