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
    // cells
    ClassDB::bind_method(D_METHOD("get_cells"), &WorldModule::get_cells);
    ClassDB::bind_method(D_METHOD("set_cells", "in_cells"), &WorldModule::set_cells);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "cells"), "set_cells", "get_cells");

    // proba
    ClassDB::bind_method(D_METHOD("get_probability"), &WorldModule::get_probability);
    ClassDB::bind_method(D_METHOD("set_probability", "in_probability"), &WorldModule::set_probability);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "probability"), "set_probability", "get_probability");
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
        dict["Position"]    = cell_itr.first;
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
    size_t sz = in_modules.size();
    cells.clear();
    for (int idx = 0; idx < sz; idx++)
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

    // update dimension 
    size = calculate_size();
}

float WorldModule::get_probability() const
{
    return probability;
}

void WorldModule::set_probability(const float& in_probability)
{
    probability = in_probability;
}

bool WorldModule::contains_cell(Ref<WorldCell> cell) const 
{
    // Modules are usually no bigger than a 5*5 so it shouldn't take long, this could still be improved upon
    for (auto itr : cells)
    {
        if (itr.second.cell == cell)
            return true;
    }
}

Vector2i WorldModule::calculate_size() const
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


std::set<Ref<WorldCell>> WorldModule::get_world_cells() const
{
    std::set<Ref<WorldCell>> ret_val;
    for (auto itr : cells)
    {
       ret_val.emplace(itr.second.cell);
    }
}