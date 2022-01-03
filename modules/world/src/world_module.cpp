/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_module.h"

// godot
#include <core/object/class_db.h>
#include <scene/resources/texture.h>

// armory
#include "world_statics.h"

using namespace armory;


void Module::_bind_methods()
{
		// Properties
	ADD_GROUP("Module", "world_module_");
    // generation system
	ADD_SUBGROUP("system", "system_");
    // cells
    ClassDB::bind_method(D_METHOD("get_cells"), &Module::get_cells);
    ClassDB::bind_method(D_METHOD("set_cells", "in_cells"), &Module::set_cells);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "cells"), "set_cells", "get_cells");

    // proba
    ClassDB::bind_method(D_METHOD("get_probability"), &Module::get_probability);
    ClassDB::bind_method(D_METHOD("set_probability", "in_probability"), &Module::set_probability);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "probability"), "set_probability", "get_probability");
}


Module::Module() : WorldResource()
{
}

Array Module::get_cells() const
{
    Array ret_val;
    for (auto cell_itr : cells)
    {
        // create dictionnary from struct:
        Dictionary dict;
        dict["Position"]    = cell_itr.first;
        dict["Rotation"]    = cell_itr.second.rotation * 90;
        dict["Cell"]        = cell_itr.second;
        ret_val.append(dict);
    }
    return ret_val;
}

void Module::set_cells(const Array& in_modules)
{
    size_t sz = in_modules.size();
    cells.clear();
    for (int idx = 0; idx < sz; idx++)
    {
        Dictionary dict     = in_modules[idx];
        Vector2i pos        = dict["Position"];
        cells[pos]          = ModuleCell(Ref<Cell>(dict["Cell"]), int(dict["Rotation"]) / 90);
    }
    // update dimension 
    size = calculate_size();
}

float Module::get_probability() const
{
    return probability;
}

void Module::set_probability(const float& in_probability)
{
    probability = in_probability;
}

bool Module::contains_cell(Ref<Cell> cell) const 
{
    // Modules are usually no bigger than a 5*5 so it shouldn't take long, this could still be improved upon
    for (auto citr : cells)
    {
       if (Ref<Cell>(citr.second) == cell)
            return true;
    }
    return false;
}

Vector2i Module::calculate_size() const
{
    // Vector2i are sorted first by x, then by Y.
    // thus biggest X is last key. you still have to search for biggest Y.
    // searching max x and y simultaneously does not add complexity though adding min 
    int max_x, max_y, min_x, min_y = 0;
    for (auto itr : cells)
    {
        min_x = (itr.first.x < min_x) ? itr.first.x : min_x;
        min_y = (itr.first.y < min_y) ? itr.first.y : min_y;
        max_x = (itr.first.x > max_x) ? itr.first.x : max_x;
        max_y = (itr.first.y > max_y) ? itr.first.y : max_y;
    }
    return Vector2i(max_x - min_x, max_y - min_y);
}


std::set<Ref<Cell>> Module::get_world_cells() const
{
    std::set<Ref<Cell>> ret_val;
    for (auto itr : cells)
    {
        if(itr.second.is_valid())
            ret_val.emplace(itr.second);
    }
}