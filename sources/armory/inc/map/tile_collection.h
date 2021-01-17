/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_COLLECTION_H
#define ARMORY_TILE_COLLECTION_H

#include "map/map_core.h"
#include "core/io/resource.h"
#include "core/variant/array.h"
#include "map/tile_mesh.h"
#include "static_helper.h" // add GETSET_SUPPORT


/** Armory namespace */
namespace Armory 
{

/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileCollection : public Resource  {
    GDCLASS(TileCollection, Resource);

protected:
    Array tileset;
    GETSET(Array, tileset)

public:

    inline int get_tile_num() const { return tileset.size(); }

    /** 
     * find and cast Variant in array to return TileMesh pointer
     */
    const TileMesh * get_tile(int index) const;

    /** 
     * create an array based on all TileMeshes contained in tileset
     */
    const Vector<TileMesh*> get_tiles() const;


#ifdef TOOLS_ENABLED
    Ref<TileMesh> import_tile;
    GET(Ref<TileMesh>, import_tile)
    void set_import_tile(const Ref<TileMesh> &p_import_tile);
#endif //TOOLS_ENABLED



public:
    static void _bind_methods();

};

} // namespace Armory

#endif //TILE_COLLECTION_H