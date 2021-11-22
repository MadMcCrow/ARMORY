/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world/world_module.h"

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
    size_t count = cells.size();
    ret_val.resize(count);
    #pragma omp parallel for
    for (int idx = 0; idx < count; ++idx)
    {
        // create dictionnary from struct:
        Dictionary dict;
        dict["Cell"] = cells[idx].cell;
        dict["Rotation"] = cells[idx].rotation;
        ret_val[idx] = dict;
    }
    return ret_val;
}

void WorldModule::set_cells(const Array& in_modules)
{
    size_t count = in_modules.size();
    cells.resize(count);
    #pragma omp parallel for
    for (int idx = 0; idx < count; ++idx)
    {
         Dictionary dict     = in_modules[idx];
         cells[idx].cell     = dict["Cell"];
         cells[idx].rotation = dict["Rotation"];
    }
}


