/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "nodes/actor_3d.h"
#include "scene/scene_string_names.h"

using namespace Armory;


Actor3D::Actor3D()
{
    connect(SceneStringNames::get_singleton()->_ready, callable_mp(this, &Actor3D::_ready));
    connect(SceneStringNames::get_singleton()->_process, callable_mp(this, &Actor3D::_process));
}

Actor3D::~Actor3D()
{
}

void Actor3D::_ready()
{

}

void Actor3D::_process( float delta)
{

}

void Actor3D::_bind_methods() 
{
    // recreation of GDScript/ GDNative functions : 
    ClassDB::bind_method(D_METHOD("_ready"), &Actor3D::_ready);
        // recreation of GDScript/ GDNative functions : 
    ClassDB::bind_method(D_METHOD("_process", "delta"), &Actor3D::_process);

}
