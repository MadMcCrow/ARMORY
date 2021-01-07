/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_manager.h"
#include "scene/resources/multimesh.h"
#include "map/tile_collection.h"
#include "grid/grid_2D.h"


using namespace Armory;


void TileManager::_ready() 
{
    updateInstanceMap();
    print_msg(this, "tilemanager is ready");
}

String TileManager::get_configuration_warning() const
{
    auto warning = Node3D::get_configuration_warning();
    if(collection.is_null())
    {
        warning += TTR("No collection set, cannot generate tiles");
    }
    if(!Cast<GridNode>(get_owner()))
    {
        warning += TTR("this node requieres to be a child of a GridNode");
    }
    return warning;
}


void TileManager::_bind_methods()
{
    ADD_GROUP("Grid", "Grid_");
	BIND_PROPERTY_GETSET(TileManager, Variant::OBJECT, collection, PROPERTY_HINT_RESOURCE_TYPE, "TileCollection");
}

void TileManager::updateInstanceMap()
{
    /*
    if (TileCollection * tileset = collection.ptr())
    {
        for (int idx = 0; idx < tileset->get_tile_num(); idx++ )
        {
            
            TileMesh m = tileset->get_tile(idx);
            if (MultiMesh v = mesh_instance_map.find(m))
            {
                 ;
            }
            else
            {
                mesh_instance_map.insert();
            }
          
        }
    }
    */
}


MultiMesh* TileManager::createMultimeshInstance(TileMesh * input)
{
    return nullptr;
}
