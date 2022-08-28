/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_tile.h"

using namespace armory;

// godot
bool compare_name(const CharString &A,const CharString &B)
{
    if (std::strcmp(A.get_data(),B.get_data()) != 0)
    {
        return false;
    }
    return true;
}

void WorldTile::_bind_methods()
{
	// Methods.

    // WorldTile Methods
    ClassDB::bind_method(D_METHOD("set_shape", "in_shape"),  &WorldTile::set_shape);
    ClassDB::bind_method(D_METHOD("get_shape"),  &WorldTile::get_shape);

    ClassDB::bind_method(D_METHOD("set_borders", "in_borders"),  &WorldTile::set_borders);
    ClassDB::bind_method(D_METHOD("get_borders"),  &WorldTile::get_borders);

    ClassDB::bind_method(D_METHOD("set_weight", "in_weight"),  &WorldTile::set_weight);
    ClassDB::bind_method(D_METHOD("get_weight"),  &WorldTile::get_weight);

    ClassDB::bind_method(D_METHOD("set_tile_3d", "in_tile_3d"),  &WorldTile::set_tile_3d);
    ClassDB::bind_method(D_METHOD("get_tile_3d"),  &WorldTile::get_tile_3d);

    ClassDB::bind_method(D_METHOD("set_tile_2d", "in_tile_2d"),  &WorldTile::set_tile_2d);
    ClassDB::bind_method(D_METHOD("get_tile_2d"),  &WorldTile::get_tile_2d);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");

    ADD_PROPERTY(PropertyInfo(Variant::INT,   "shape",   PROPERTY_HINT_ENUM, "TileableShapes"),   "set_shape", "get_shape");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "borders", PROPERTY_HINT_ARRAY_TYPE, "String"),   "set_borders", "get_borders");

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT,   "weight"),   "set_weight",     "get_weight");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,   "tile_2d", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),  "set_tile_2d",    "get_tile_2d");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,   "tile_3d", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"),       "set_tile_3d",    "get_tile_3d");

    BIND_ENUM_CONSTANT(WorldTile::Triangle);
	BIND_ENUM_CONSTANT(WorldTile::Square);
    BIND_ENUM_CONSTANT(WorldTile::Hexagon);

}


Ref<WorldTile> WorldTile::rotate(int count) const {
    Ref<WorldTile> ret_val = duplicate(false);
    count = count % shape; // avoid doing the rotate too much
    for (int t = 0; t < count; t++) {
        std::rotate(ret_val->borders.rbegin(), ret_val->borders.rbegin() + 1, ret_val->borders.rend());
    }
    return ret_val;
}

void WorldTile::set_borders(const PackedStringArray& in_borders) {
    borders.clear();
    borders.reserve(shape);
    for (uint8_t idx = 0; idx < shape; idx++) {
        if (in_borders.size() > idx) {
            borders.push_back(String(in_borders[idx]).utf8());
        } else {
            borders.push_back(String().utf8());
        }
    }
}

PackedStringArray WorldTile::get_borders() const {
    PackedStringArray ret_val;
    ret_val.resize(shape);
    for (uint8_t idx = 0; idx < shape; idx++)
    {
        if (borders.size() > idx) {
            ret_val[idx] = String(borders[idx].get_data());
        } else {
            ret_val[idx] = String();
        }     
    }
    return ret_val;
}