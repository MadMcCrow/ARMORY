/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include "scene/3d/node_3d.h"
#include "core/object/reference.h"
#include "map/grid_node.h"
#include "map/tile_collection.h"
#include "static_helper.h" // add GETSET_SUPPORT



/** Armory namespace */
namespace Armory {


/**
 *  TileManager handles the tiles for the Grid map
 */
class TileManager : public Node3D  {
    GDCLASS(TileManager, Node3D);
protected:

    Ref<TileCollection> collection;
    GETSET( Ref<TileCollection> , collection)

public:

    virtual String get_configuration_warning() const override;

public:
    static void _bind_methods();

};

} // namespace Armory

#endif //TILE_MANAGER_H
