/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_mesh.h"
//#include "core/string/translation.h"

using namespace Armory;

void TileMesh::_bind_methods()
{
    //BIND_GETSET(geometry, TileMesh);
    //BIND_GETSET(height, TileMesh);

    // bin enum Geometry
    BIND_ENUM_CONSTANT(flat);
    BIND_ENUM_CONSTANT(straight);
    BIND_ENUM_CONSTANT(cross);
    BIND_ENUM_CONSTANT(angle_convex);
    BIND_ENUM_CONSTANT(angle_concave);
    BIND_ENUM_CONSTANT(T_convex);
    BIND_ENUM_CONSTANT(T_concave);
    BIND_ENUM_CONSTANT(all_sides);

    // bin enum Height
    BIND_ENUM_CONSTANT(sea);
    BIND_ENUM_CONSTANT(plain);
    BIND_ENUM_CONSTANT(hill_0);
    BIND_ENUM_CONSTANT(hill_1);
    BIND_ENUM_CONSTANT(hill_2);
    BIND_ENUM_CONSTANT(mountain);

    // bind properties:
    ADD_PROPERTY()
    //ADD_PROPERTY_GETSET( Variant::OBJECT, mesh,    PROPERTY_HINT_RESOURCE_TYPE, "Mesh to use");
    //ADD_PROPERTY_GETSET( Variant::INT,    variant, PROPERTY_HINT_ENUM, "flat, straight, cross, angle_convex, angle_concave, T_convex, T_concave, all_sides");
    BIND_PROPERTY_GETSET(TileMesh, Variant::INT,    height,   PROPERTY_HINT_ENUM, "sea, plain, hill_0, hill_1, hill_2, mountain");
}