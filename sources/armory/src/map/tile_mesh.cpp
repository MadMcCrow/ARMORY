/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_mesh.h"

using namespace Armory;


void TileMesh::set_height(unsigned int h)
{
    height = clamp<unsigned int>( h, 0b00, 0b11);
}

void TileMesh::_bind_methods()
{ 
    // Bind our enum
    BIND_ENUM_CONSTANT(flat);
    BIND_ENUM_CONSTANT(straight);
    BIND_ENUM_CONSTANT(cross);
    BIND_ENUM_CONSTANT(angle_convex);
    BIND_ENUM_CONSTANT(angle_concave);
    BIND_ENUM_CONSTANT(T_convex);
    BIND_ENUM_CONSTANT(T_concave);
    BIND_ENUM_CONSTANT(all_sides);
    BIND_PROPERTY_ENUM(TileMesh, type, "flat, straight, cross, angle_convex, angle_concave, T_convex, T_concave, all_sides")

    BIND_PROPERTY_GETSET(TileMesh, Variant::INT,    height,  PROPERTY_HINT_RANGE, "0,3,1;");
    BIND_PROPERTY_GETSET(TileMesh, Variant::BOOL,   is_land, PROPERTY_HINT_NONE, "Land");
}