/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/tile_instance.h"
#include "map/tile_manager.h"

using namespace Armory;


void TileInstance::update_multimesh(Ref<TileMesh> tile_mesh)
{
    if (tile_mesh.is_valid())
    {
        if (tile_mesh->get_mesh().is_valid())
        {
            multimesh = Ref<MultiMesh>();
            /*
            if (multimesh.is_valid())
            {
                multimesh.unref();
            }
            */
            multimesh.instance();
            multimesh->set_mesh(tile_mesh->get_mesh());
            multimesh->set_transform_format(MultiMesh::TransformFormat::TRANSFORM_3D);
        }
    }
}

void TileInstance::_bind_methods()
{
    BIND_PROPERTY_GETSET(TileInstance, Variant::OBJECT, tile_mesh, PROPERTY_HINT_RESOURCE_TYPE, "TileMesh");
}


String TileInstance::get_configuration_warning() const
{
    auto warning = Node3D::get_configuration_warning();
    if (!Cast<TileManager>(get_parent()))
    {
        warning += TTR("this node requieres to be a child of a TileManager");
    }
    return warning;
}


void TileInstance::set_tile_mesh(const Ref<TileMesh> &p_tile_mesh)
{
    tile_mesh = p_tile_mesh;
    if (tile_mesh.is_valid())
    {
        if (tile_mesh->get_mesh().is_valid())
        {
            set_base(tile_mesh->get_mesh()->get_rid());
            update_multimesh(tile_mesh);
            return;
        }
    }
    set_base(RID());
}

Vector<Face3> TileInstance::get_faces(uint32_t p_usage_flags) const
{
    return Vector<Face3>();
}

AABB TileInstance::get_aabb() const
{
    if (tile_mesh.is_valid())
    {
        if (tile_mesh->get_mesh().is_valid())
            return tile_mesh->get_mesh()->get_aabb();
    }
    return AABB();
}

TileInstance::TileInstance()
{
}

TileInstance::~TileInstance()
{
}
