/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world/world_module.h"
#include "world/world_statics.h"
#include <core/object/class_db.h>

using namespace armory;

void WorldModule::_bind_methods()
{
		// Properties
	ADD_GROUP("WorldModule", "world_module_");
    // generation system
	ADD_SUBGROUP("system", "system_");
    // cell type
    ClassDB::bind_method(D_METHOD("get_cells"), &WorldModule::get_cells);
    ClassDB::bind_method(D_METHOD("set_cells", "in_cells"), &WorldModule::set_cells);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "cells"), "set_cells", "get_cells");
}


WorldModule::WorldModule() : Resource()
{

}


Array WorldModule::get_cells() const
{
    Array ret_val;
    for (auto cell_itr : cells)
    {
        // create dictionnary from struct:
        Dictionary dict;
        dict["Cell"]        = cell_itr.second.cell;
        dict["Position"]   = cell_itr.first;
        switch(cell_itr.second.rotation)
        {
            default:
            case WorldStatics::Direction::North :
            dict["Rotation"] = WorldStatics::north();
            break;
            case WorldStatics::Direction::South:
            dict["Rotation"] = WorldStatics::south();
            break;
            case WorldStatics::Direction::East :
            dict["Rotation"] = WorldStatics::east();
            break;
            case WorldStatics::Direction::West :
            dict["Rotation"] =  WorldStatics::west();
            break;
        }

        ret_val.append(dict);
    }
    return ret_val;
}

void WorldModule::set_cells(const Array& in_modules)
{
    size_t size = in_modules.size();
    cells.clear();
    for (int idx = 0; idx < size; idx++)
    {
        Dictionary dict     = in_modules[idx];
        Vector2i pos        = dict["Position"];
        cells[pos].cell     = dict["Cell"];
        // direction
        String dir = dict["Rotation"];
        if (dir.begins_with("W"))           cells[pos].rotation = WorldStatics::Direction::West;
        else if (dir.begins_with("E"))      cells[pos].rotation = WorldStatics::Direction::East;
        else if (dir.begins_with("S"))      cells[pos].rotation = WorldStatics::Direction::South;
        else                                cells[pos].rotation = WorldStatics::Direction::North;
    }
}
