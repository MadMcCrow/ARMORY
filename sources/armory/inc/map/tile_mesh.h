/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef TILE_MESH_H
#define TILE_MESH_H

#include "map/map_core.h"
#include "scene/resources/mesh.h"
#include "static_helper.h" // add GETSET_SUPPORT

/** Armory namespace */
namespace Armory 
{

namespace Tile 
{   
    // simple enum to describe type
    enum class Variant : char
    {
        flat,
        straight,
        cross,
        angle_convex,
        angle_concave,
        T_convex,
        T_concave,
        all_sides
    };

    enum class Height : char
    {
        sea,
        plain,
        hill_0,
        hill_1,
        hill_2,
        mountain
    };

} // namespace Tile

/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileMesh : public Mesh  {
    GDCLASS(TileMesh, Mesh);

public:
    //static void _bind_methods();


};

} // namespace Armory

#endif //TILE_COLLECTION_H