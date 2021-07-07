/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_mesh.h"
#include "scene/resources/mesh.h" // Mesh resource

using namespace Armory;

void TileMesh::set_height(unsigned int h)
{
    height = clamp<unsigned int>(h, 0b00, 0b11);
}

void TileMesh::_bind_methods()
{
    // Bind our enum
    BIND_ENUM_CONSTANT(Geometry::flat);
    BIND_ENUM_CONSTANT(Geometry::straight);
    BIND_ENUM_CONSTANT(Geometry::cross);
    BIND_ENUM_CONSTANT(Geometry::angle_convex);
    BIND_ENUM_CONSTANT(Geometry::angle_concave);
    BIND_ENUM_CONSTANT(Geometry::T_convex);
    BIND_ENUM_CONSTANT(Geometry::T_concave);
    BIND_ENUM_CONSTANT(Geometry::all_sides);
    BIND_PROPERTY_ENUM(TileMesh, type, "flat, straight, cross, angle_convex, angle_concave, T_convex, T_concave, all_sides");

    // Bind our enum
    BIND_ENUM_CONSTANT(Modifier::no_modifier);
    BIND_ENUM_CONSTANT(Modifier::river);
    BIND_ENUM_CONSTANT(Modifier::trees);
    BIND_ENUM_CONSTANT(Modifier::rocks);
    BIND_ENUM_CONSTANT(Modifier::canyon);
    BIND_PROPERTY_ENUM(TileMesh, modif, "none, river, trees, rocks, canyon");

    BIND_PROPERTY_GETSET(TileMesh, Variant::INT, height, PROPERTY_HINT_RANGE, "0,3,1;");
    BIND_PROPERTY_GETSET(TileMesh, Variant::BOOL, is_land, PROPERTY_HINT_NONE, "Land");
    BIND_PROPERTY_GETSET(TileMesh, Variant::OBJECT, mesh, PROPERTY_HINT_RESOURCE_TYPE, "Mesh");
}

Ref<TileMesh> TileMesh::from_mesh(Ref<ArrayMesh> src_mesh)
{
    Ref<TileMesh> mesh;
    mesh.instantiate();
    mesh->set_mesh(src_mesh);
    return mesh;
}