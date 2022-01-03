/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_module.h"

#include <core/object/class_db.h>
#include <scene/resources/texture.h>

#include "world_statics.h"

using namespace armory;

void ModuleCell::_bind_methods()
{
    ADD_GROUP("Module", "world_module_");
    // generation system
	// ADD_SUBGROUP("system", "system_");
    // cells
    ClassDB::bind_method(D_METHOD("get_cell"), &ModuleCell::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell", "in_cell"), &ModuleCell::set_cell);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cell"), "set_cell", "get_cell");

    ClassDB::bind_method(D_METHOD("get_rotation"), &ModuleCell::get_rotation);
    ClassDB::bind_method(D_METHOD("set_rotation", "in_rotation"), &ModuleCell::set_rotation);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cell"), "set_rotation", "get_rotation");
}

Ref<Cell> ModuleCell::get_cell() const { return cell;}
void ModuleCell::set_cell(const Ref<Cell> & in_cell) {cell = in_cell;}
int ModuleCell::get_rotation() const {return static_cast<int>(rotation);}
void ModuleCell::set_rotation(const int& in_rotation) {rotation = static_cast<WorldStatics::Direction>(in_rotation);}

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


Module::Module() : Resource()
{

}


Array Module::get_cells() const
{
    Array ret_val;
    for (auto cell_itr : cells)
    {
        // create dictionnary from struct:
        Dictionary dict;
        dict["Cell"]        = cell_itr.second;
        dict["Position"]    = cell_itr.first;
        if(cell_itr.second.is_valid())
        {
            switch(cell_itr.second->get_rotation())
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
        }
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
        cells[pos]          = dict["Cell"];
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
        if(citr.second.is_valid())
            if (citr.second->cell == cell)
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
            ret_val.emplace(itr.second->cell);
    }
}