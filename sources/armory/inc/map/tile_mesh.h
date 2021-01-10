/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_MESH_H
#define ARMORY_TILE_MESH_H


//#include "core/variant/binder_common.h"  // VARIANT_ENUM_CAST
#include "scene/resources/mesh.h"        // Mesh resource

#include "static_helper.h"               // add GETSET_SUPPORT



namespace Armory
{

/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileMesh : public ArrayMesh  {
    GDCLASS(TileMesh, ArrayMesh);

public:

    /**
     *  Geometry describe how this tile interact with others 
     */
    enum Geometry  {
        flat,
        straight,
        cross,
        angle_convex,
        angle_concave,
        T_convex,
        T_concave,
        all_sides,
        max = all_sides
    };

    /**
     *  is_land is true for land tiles,
     *  false for sea
     */
    bool is_land = true;
    GETSET(bool, is_land)

    /**
     *  height {0,1,2,3}
     */
    unsigned int height : 2;
    GET(unsigned int, height);
    void set_height(unsigned int h);
 
    /**
     *  type of geometry this tile has
     */
    Geometry type;
    GETSET_COPY(Geometry, type)

    void set_geometry(int type) {type = static_cast<Geometry>(type % (static_cast<int>(Geometry::max) + 1));}

    static void _bind_methods();

};

} // namespace Armory

// declare enums
VARIANT_ENUM_CAST(Armory::TileMesh::Geometry);


#endif //TILE_MESH_H