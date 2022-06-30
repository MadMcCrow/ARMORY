/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_tile.h"

// godot
#include <core/object/class_db.h>
#include <core/error/error_macros.h>
#include <core/math/color.h>


using namespace armory;

bool compare_name(const CharString &A,const CharString &B)
{
    //if (std::strcmp(A.ptr(),B.ptr()) != 0)
    {
        WARN_PRINT_ED("compare_name : Incompatible A=" + String(A.ptr()) + " B=" + String(B.ptr()));
    //    return false;
    }
    return true;
}

void WorldTile::_bind_methods()
{
	// Methods.

    // WorldTile Methods

    //
    ClassDB::bind_method(D_METHOD("set_left", "in_left"),   &WorldTile::set_left);
    ClassDB::bind_method(D_METHOD("set_right", "in_right"), &WorldTile::set_right);
    ClassDB::bind_method(D_METHOD("set_up", "in_up"),       &WorldTile::set_up);
    ClassDB::bind_method(D_METHOD("set_down", "in_down"),   &WorldTile::set_down);

    ClassDB::bind_method(D_METHOD("get_left"),  &WorldTile::get_left);
    ClassDB::bind_method(D_METHOD("get_right"), &WorldTile::get_right);
    ClassDB::bind_method(D_METHOD("get_up"),    &WorldTile::get_up);
    ClassDB::bind_method(D_METHOD("get_down"),  &WorldTile::get_down);

    ClassDB::bind_method(D_METHOD("set_weight", "in_weight"),  &WorldTile::set_weight);
    ClassDB::bind_method(D_METHOD("get_weight"),  &WorldTile::get_weight);

    ClassDB::bind_method(D_METHOD("set_tile_3d", "in_tile_3d"),  &WorldTile::set_tile_3d);
    ClassDB::bind_method(D_METHOD("get_tile_3d"),  &WorldTile::get_tile_3d);

    ClassDB::bind_method(D_METHOD("set_tile_2d", "in_tile_2d"),  &WorldTile::set_tile_2d);
    ClassDB::bind_method(D_METHOD("get_tile_2d"),  &WorldTile::get_tile_2d);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");

    ADD_PROPERTY(PropertyInfo(Variant::STRING,   "left"),   "set_left",     "get_left");
    ADD_PROPERTY(PropertyInfo(Variant::STRING,   "right"),  "set_right",    "get_right");
    ADD_PROPERTY(PropertyInfo(Variant::STRING,   "up"),     "set_up",       "get_up");
    ADD_PROPERTY(PropertyInfo(Variant::STRING,   "down"),   "set_down",     "get_down");


    ADD_PROPERTY(PropertyInfo(Variant::FLOAT,   "weight"),   "set_weight",     "get_weight");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,   "tile_2d", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),  "set_tile_2d",    "get_tile_2d");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,   "tile_3d", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"),       "set_tile_3d",    "get_tile_3d");
}


void WorldTile::reload_from_file()
{
    // resave border names
    set_left(get_left().camelcase_to_underscore());
    set_right(get_right().camelcase_to_underscore());
    set_up(get_up().camelcase_to_underscore());
    set_down(get_down().camelcase_to_underscore());
    Resource::reload_from_file(); // call to super
}

Ref<WorldTile> WorldTile::rotate() const
{
    // copy but subresources stays the same :
    Ref<WorldTile> ret_val = duplicate(false);
    // rotate :
    ret_val->left   = up;
    ret_val->up     = right;
    ret_val->right  = down;
    ret_val->down   = left;
    return ret_val;
}

bool WorldTile::is_compatible(const Ref<WorldTile> &left_tile, const Ref<WorldTile> &right_tile, const Ref<WorldTile> &up_tile, const Ref<WorldTile> &down_tile) const
{
    if (left_tile.is_valid())
    {
        if (!compare_name(left_tile->right,left))
            return false;
    }
    if (right_tile.is_valid())
    {
        if (!compare_name(right_tile->left,right))
            return false;
    }
    if (up_tile.is_valid())
    {
        if (!compare_name(up_tile->down,up))
            return false;
    }
    if (down_tile.is_valid())
    {
        if (!compare_name(down_tile->up,down))
            return false;
    }

    {
        WARN_PRINT_ED("is_compatible : compatible  tile");
    }

    return true;
}