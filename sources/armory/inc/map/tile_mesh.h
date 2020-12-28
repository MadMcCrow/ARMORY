/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef TILE_MESH_H
#define TILE_MESH_H


#include "core/variant/binder_common.h"  // VARIANT_ENUM_CAST
#include "scene/resources/mesh.h"        // Mesh resource

#include "static_helper.h"               // add GETSET_SUPPORT



namespace Armory
{

/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileMesh : public Resource  {
    GDCLASS(TileMesh, Resource);

public:

    // simple enum to describe type
    enum Geometry  {
        flat,
        straight,
        cross,
        angle_convex,
        angle_concave,
        T_convex,
        T_concave,
        all_sides
    };

    
    // simple enum to describe height
    enum Height {
        sea,
        plain,
        hill_0,
        hill_1,
        hill_2,
        mountain
    };


    static void _bind_methods();

    /**
     *  mesh is the real ressource we'll load
     */
    Ref<Mesh> mesh;
    GETSET(Ref<Mesh>, mesh)

    /**
     *  height represent the height to use
     */
    Height height;
    GETSET(Height, height)
 
    /**
     *  variant represent the transition shape we can have
     */
    Geometry geometry;
    GETSET(Geometry, geometry)

};

} // namespace Armory

// declare enums
VARIANT_ENUM_CAST(Armory::TileMesh::Geometry);
VARIANT_ENUM_CAST(Armory::TileMesh::Height);


#endif //TILE_MESH_H