/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef TILE_COLLECTION_H
#define TILE_COLLECTION_H

#include "map/map_core.h"
#include "core/io/resource.h"
#include "static_helper.h" // add GETSET_SUPPORT

/** Armory namespace */
namespace Armory 
{


/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileCollection : public Resource  {
    GDCLASS(TileCollection, Resource);

public:
    static void _bind_methods();


};

} // namespace Armory

#endif //TILE_COLLECTION_H