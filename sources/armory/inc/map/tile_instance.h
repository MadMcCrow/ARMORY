/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_INSTANCE_H
#define ARMORY_TILE_INSTANCE_H

#include "scene/3d/multimesh_instance_3d.h"
#include "map/map_core.h"
#include "static_helper.h" // add GETSET_SUPPORT

/** Armory namespace */
namespace Armory 
{

/**
 *  GridNode3D implements gridNode with 3D 
 */
class TileInstance : public MultiMeshInstance3D  {
    GDCLASS(TileInstance, MultiMeshInstance3D);

public:

    MapData TileInfo;


    static void _bind_methods();

};

} // namespace Armory

#endif //ARMORY_TILE_INSTANCE_H