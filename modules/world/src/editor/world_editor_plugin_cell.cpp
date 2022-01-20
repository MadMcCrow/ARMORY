/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin_cell.h"
#include <core/io/resource_saver.h>
#include <editor/editor_inspector.h>
#include <scene/gui/box_container.h>

#include "world_cell.h"


using namespace armory;

void WorldEditorPluginCell::edit(const Ref<Cell> &Res)
{
    // Safety first
    if (!editor_container || !Res.ptr())
    {
        return;
    }
 
    current_cell = Res;
    _update_properties();

}

void WorldEditorPluginCell::apply_changes()
{
    _update_properties();
}


void WorldEditorPluginCell::_update_properties()
{
    if (!editor_container || !current_cell.ptr())
    {
        return;
    }

    if (cell_name_editor)
    {
        const auto pinfo = PropertyInfo(Variant::STRING_NAME, "cell_type_name");
        cell_name_editor->set_object_and_property(current_cell.ptr(), pinfo.name);
        cell_name_editor->update_property();
    }
    else
    {
        auto cell_name_value = current_cell->get_cell_type();
        const auto pinfo = PropertyInfo(Variant::STRING_NAME, "cell_type_name");
        cell_name_editor = EditorInspector::instantiate_property_editor(current_cell.ptr(), pinfo.type, pinfo.name , pinfo.hint, pinfo.hint_string, pinfo.usage);
        cell_name_editor->set_label("Type Name");
        cell_name_editor->set_object_and_property(current_cell.ptr(), pinfo.name);
	    cell_name_editor->connect(SNAME("property_changed"), callable_mp(this , &WorldEditorPluginCell::_cell_property_changed));
        cell_name_editor->update_property();
        cell_name_editor->show();
        editor_container->add_child(cell_name_editor);
    }

    for (auto pe : cell_data_editors)
    {
        editor_container->remove_child(pe);
        // should I do that ?
        memdelete(pe);
    }
}

	/** cell property changed, need to update it*/
void WorldEditorPluginCell::_cell_property_changed(const String &p_path, const Variant &p_value, const String &p_name, bool p_changing)
{
    const auto cell_type_info = PropertyInfo(Variant::STRING_NAME, "cell_type_name");
    // this is confusing but path should be used, not name
    if (p_path == cell_type_info.name)
    {
        if (current_cell.ptr())
        {
            current_cell->set_cell_type(p_value);
            // no need to save, it just works (tm)
            // ResourceSaver::save(current_cell->get_path(), current_cell);
        }
        else
        {
            WARN_PRINT("could not edit cell, current_cell was not valid");
        }
        // nothing more should be done
        return;
    }
    
    // could not make sens of the edit, we need to do something about this
    WARN_PRINT("property name was " + p_name + ", path was " + p_path + ", Value was " + p_value);
}

WorldEditorPluginCell::WorldEditorPluginCell() : ScrollContainer()
{
    editor_container = memnew(VBoxContainer);
    editor_container->set_name(TTR("vertical container"));
    editor_container->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    editor_container->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    editor_container->show();
    add_child(editor_container);
}

WorldEditorPluginCell::~WorldEditorPluginCell()
{
}


#endif // TOOLS_ENABLED
