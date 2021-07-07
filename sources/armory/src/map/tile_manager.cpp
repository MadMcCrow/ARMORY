/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_manager.h"
#include "scene/resources/multimesh.h"
#include "map/tile_collection.h"
#include "map/tile_instance.h"
#include "grid/grid_2D.h"

using namespace Armory;

void TileManager::ready()
{
    owning_grid = get_owning_grid();
    updateInstanceMap();
    print_msg(this, "tilemanager is ready");
}

void TileManager::tree_update()
{
    owning_grid = get_owning_grid();
    updateInstanceMap();
}

/*
String TileManager::get_configuration_warning() const
{
    auto warning = Node3D::get_configuration_warning();
    if (get_owning_grid() == nullptr)
    {
        warning += TTR("this node requieres to be a child of a GridNode");
    }
    return warning;
}
*/

void TileManager::_bind_methods()
{

}

void TileManager::updateInstanceMap()
{

    const int num = get_child_count();
    for (int idx = 0; idx < num; idx++)
    {
        if (auto instance = Cast<TileInstance>(get_child(idx)))
        {
            if (instance->tile_mesh.is_valid())
            {
                const int count = get_instance_num(instance->tile_mesh);
                instance->get_multimesh()->set_instance_count(count);
                // @todo: dynamically set visible count
                instance->get_multimesh()->set_visible_instance_count(count);
                for (int t = 0; t < count; t++)
                {
                    print_msg(this, String("generating a new instance"));
                    instance->get_multimesh()->set_instance_transform(t, Transform3D(Basis(), Vector3(t * 10, 0, 0)));
                }
            }
        }
    }
}

int TileManager::get_instance_num(Ref<TileMesh> tilemesh) const
{
    if (owning_grid != nullptr)
    {
        if (tilemesh.is_valid())
        {
            MapData dat;
            dat.height = tilemesh->height;
            dat.modifier = tilemesh->modif != TileMesh::Modifier::no_modifier ? 1 : 0;
            dat.sign = tilemesh->is_land ? 1 : 0;
            return owning_grid->get_data_count(dat);
        }
    }
    return 0;
}