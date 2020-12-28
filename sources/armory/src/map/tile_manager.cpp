/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_manager.h"
#include "map/tile_collection.h"
#include "grid/grid_2D.h"


using namespace Armory;


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
	BIND_PROPERTY_GETSET(TileManager, Variant::OBJECT, collection, PROPERTY_HINT_RESOURCE_TYPE, "collection");
}