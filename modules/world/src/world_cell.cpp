/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_cell.h"

// godot
#include <scene/resources/texture.h>

// armory
#include "world_statics.h"

using namespace armory;

void Cell::_bind_methods()
{
	// Properties
	ADD_GROUP("Cell", "world_cell_");
    // generation system
	ADD_SUBGROUP("system", "system_");
    // cell type
    ClassDB::bind_method(D_METHOD("get_cell_type"), &Cell::get_cell_type);
	ClassDB::bind_method(D_METHOD("set_cell_type", "cell_type"), &Cell::set_cell_type);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "cell_type_name"), "set_cell_type", "get_cell_type");
    // 2d tile
	ClassDB::bind_method(D_METHOD("get_cell_data"), &Cell::get_cell_data);
	ClassDB::bind_method(D_METHOD("set_cell_data", "in_cell_data"), &Cell::set_cell_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cell_data"), "set_cell_data", "get_cell_data");
}


Cell::Cell() : WorldResource()
{

}

StringName Cell::get_cell_type() const
{
    return cell_type_name;
}

void Cell::set_cell_type(const StringName &in_cell_type)
{
    // todo : extra checks
    cell_type_name = in_cell_type;
}

Dictionary Cell::get_cell_data() const
{
    return cell_data;
}

void Cell::set_cell_data(const Dictionary &in_cell_data)
{
    cell_data = in_cell_data;
}