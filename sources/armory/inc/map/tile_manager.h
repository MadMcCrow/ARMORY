/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef GRID_NODE_3D_H
#define GRID_NODE_3D_H


#include "grid_node.h"
#include "scene/3d/node_3d.h"
#include "static_helper.h" // add GETSET_SUPPORT

/** Armory namespace */
namespace Armory {


/**
 *  TileManager handles the tiles for the Grid map
 */
class TileManager : public Node3D  {
    GDCLASS(TileManager, Node3D);

public:
    static void _bind_methods();
};

} // namespace Armory

#endif //GRID_NODE_3D_H
