/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_MESH_H
#define ARMORY_TILE_MESH_H

//#include "core/variant/binder_common.h"  // VARIANT_ENUM_CAST
#include "scene/resources/multimesh.h"
#include "static_helper.h" // add GETSET_SUPPORT

namespace Armory
{
    /**
     *  GridNode3D implements gridNode with 3D 
     */
    class TileMesh : public MultiMesh
    {
        GDCLASS(TileMesh, MultiMesh);
        RES_BASE_EXTENSION("tilemesh");

    public:

        /**
         *  Geometry describe how this tile interact with others 
         */
        enum Geometry
        {
            none,
            flat,
            straight,
            cross,
            angle_convex,
            angle_concave,
            T_convex,
            T_concave,
            all_sides,
            g_max = all_sides
        };

        /**
         *  geometry modifier, this only works if Geometry is none
         */
        enum Modifier
        {
            no_modifier,
            river,
            trees,
            rocks,
            canyon,
            m_max = canyon
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
        GETSET_COPY(Geometry, type);
        void set_geometry(int i_type) { type = static_cast<Geometry>(i_type % (static_cast<int>(Geometry::g_max) + 1)); }


        /**
         *  type of geometry this tile has
         */
        Modifier modif;
        GETSET_COPY(Modifier, modif)
        void set_modifier(int i_modif) { modif = static_cast<Modifier>(i_modif % (static_cast<int>(Modifier::m_max) + 1)); }

        static void _bind_methods();

        static Ref<TileMesh> from_mesh(Ref<ArrayMesh> src_mesh);
    };

} // namespace Armory

// declare enums
VARIANT_ENUM_CAST(Armory::TileMesh::Geometry);
VARIANT_ENUM_CAST(Armory::TileMesh::Modifier);

#endif //TILE_MESH_H