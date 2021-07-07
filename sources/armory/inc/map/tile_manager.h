/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_MANAGER_H
#define ARMORY_TILE_MANAGER_H

// godot includes
#include "core/templates/map.h"
#include "map/tile_mesh.h"

// Armory includes
#include "nodes/actor_3d.h"
#include "map/grid_node.h"
#include "map/tile_collection.h"
#include "static_helper.h" // add GETSET_SUPPORT

// forward declaration
class MultiMesh;

/** Armory namespace */
namespace Armory
{

    /**
 *  TileManager handles the tiles for the Grid map
 */
    class TileManager : public Actor3D
    {
        GDCLASS(TileManager, Actor3D);

    public:
        virtual void ready() override;
        virtual void tree_update() override;

    protected:

        /**
         *  update the instances to match collection
         */
        virtual void updateInstanceMap();

        /**
         *  get the info on how many instances to spawn
         *  @todo : maybe move this to cpp only
         */
        virtual int get_instance_num(Ref<TileMesh> tilemesh) const;

    public:

        //virtual String get_configuration_warning() const override;

    public:
        static void _bind_methods();

    private:

        GridNode* owning_grid = nullptr;

        GridNode* get_owning_grid() const {return Cast<GridNode>(get_parent());}
    };

} // namespace Armory

#endif //ARMORY_TILE_MANAGER_H
