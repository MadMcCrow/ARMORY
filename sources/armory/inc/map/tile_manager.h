/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_TILE_MANAGER_H
#define ARMORY_TILE_MANAGER_H

// godot includes
#include "core/templates/map.h"
#include "core/object/reference.h"

// Armory includes
#include "nodes/actor_3d.h"
#include "map/grid_node.h"
#include "map/tile_collection.h"
#include "static_helper.h" // add GETSET_SUPPORT


// forward declaration
class MultiMesh;

/** Armory namespace */
namespace Armory {


/**
 *  TileManager handles the tiles for the Grid map
 */
class TileManager : public Actor3D  {
    GDCLASS(TileManager, Actor3D);

public:

    virtual void _ready() override;

protected:

    /**
     *  the collection to use
     */
    Ref<TileCollection> collection;
    GETSET( Ref<TileCollection> , collection)


    /**
     *  for each TileMesh, we have a MultiMesh to have instances in the world
     */
    //Map<int, Mesh*> mesh_instance_map;


    /**
     *  update the instances to match collection
     */
    virtual void updateInstanceMap();




public:

    virtual String get_configuration_warning() const override;

public:
    static void _bind_methods();
};

} // namespace Armory

#endif //ARMORY_TILE_MANAGER_H
