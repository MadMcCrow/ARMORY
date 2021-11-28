/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world/world_cell.h"
#include "world/world_statics.h"

using namespace armory;

void WorldCell::_bind_methods()
{
	// Properties
	ADD_GROUP("WorldCell", "world_cell_");
    // generation system
	ADD_SUBGROUP("system", "system_");
    // cell type
    ClassDB::bind_method(D_METHOD("get_cell_type"), &WorldCell::get_cell_type);
	ClassDB::bind_method(D_METHOD("set_cell_type", "cell_type"), &WorldCell::set_cell_type);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "cell_type_name"), "set_cell_type", "get_cell_type");
    // drawing 2d
    ADD_SUBGROUP("2D", "draw_2d_");
    // 2d tile
	ClassDB::bind_method(D_METHOD("get_tile_2d"), &WorldCell::get_tile_2d);
	ClassDB::bind_method(D_METHOD("set_tile_2d", "in_tile_2d"), &WorldCell::set_tile_2d);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tile_2d"), "set_tile_2d", "get_tile_2d");
}


WorldCell::WorldCell() : Resource()
{

}

StringName WorldCell::get_cell_type() const
{
    return cell_type_name;
}

void WorldCell::set_cell_type(const StringName &in_cell_type)
{
    // todo : extra checks
    cell_type_name = in_cell_type;
}

Ref<Texture2D> WorldCell::get_tile_2d() const
{
    return tile_2d;
}

void WorldCell::set_tile_2d(const  Ref<Texture2D> &in_tile_2d)
{
    tile_2d = in_tile_2d;
}