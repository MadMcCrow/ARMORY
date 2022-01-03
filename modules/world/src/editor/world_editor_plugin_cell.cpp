/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#if TOOLS_ENABLED

#include "editor/world_editor_plugin_cell.h"
#include <editor/editor_inspector.h>
#include "world_cell.h"


using namespace armory;

void WorldEditorPluginCell::edit(const Ref<Cell> &Res)
{
    if (cell_inspector)
    {
        if (Cell* c = const_cast<Cell*>(Res.ptr()))
        {
            cell_inspector->edit(c);
        }
    }
}

WorldEditorPluginCell::WorldEditorPluginCell() : PanelContainer()
{
    cell_inspector = memnew(EditorInspector);
    cell_inspector->set_name(TTR("Cell Inspector"));
    cell_inspector->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    cell_inspector->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    cell_inspector->show();
    add_child(cell_inspector);
}

WorldEditorPluginCell::~WorldEditorPluginCell()
{
}


#endif // TOOLS_ENABLED
