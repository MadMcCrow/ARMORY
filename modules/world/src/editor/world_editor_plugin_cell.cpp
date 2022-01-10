/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin_cell.h"

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

    for (auto pe : property_editors)
    {
        editor_container->remove_child(pe);
        // should I do that ?
        memdelete(pe);
    }

    property_editors = {};

    if (Cell* c = const_cast<Cell*>(Res.ptr()))
    { 
        const auto pinfo = PropertyInfo(Variant::STRING_NAME, "cell_type_name");
        auto ed =  EditorInspector::instantiate_property_editor(c, pinfo.type, pinfo.name , pinfo.hint, pinfo.hint_string, pinfo.usage);
        ed->set_label(pinfo.name);
        ed->set_object_and_property(c, pinfo.name);
        ed->update_property();
        //ed->set_v_size_flags(Control::SIZE_EXPAND);
        //ed->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        ed->show();
        editor_container->add_child(ed);
        property_editors.push_back(ed);
    }
}

void WorldEditorPluginCell::apply_changes()
{

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
