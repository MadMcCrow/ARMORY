/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "camera/camera_move.h"
#include "scene/main/viewport.h"

using namespace ARMORY;


CameraMove::CameraMove() : KinematicBody3D()
{
}

CameraMove::~CameraMove()
{
}


void CameraMove::ready()
{
    cumulative_move_input = Vector3(0.f,0.f,0.f);
    set_physics_process(true);
}

void CameraMove::physics_process(float delta)
{
    velocity = Vector3();

    if (cumulative_move_input != Vector3())
    {
        auto basis = get_transform().get_basis();
        const Vector3 ws_movement =(basis.get_row(2) * cumulative_move_input.z + basis.get_row(0) * cumulative_move_input.x);
        velocity =  ws_movement * move_speed * delta;
        cumulative_move_input = Vector3(0.f,0.f,0.f);
    }
    velocity.y = camera_gravity * delta * -1;
    velocity = move_and_slide(velocity, Vector3(0.f,1.f,0.f), false, 4, Math::deg2rad(90.f), false );
}

void CameraMove::add_move_input(const Vector3 &direction_local_space)
{
    cumulative_move_input += direction_local_space.normalized();
}

void CameraMove::_bind_methods()
{
    BIND_PROPERTY_GETSET(CameraMove, Variant::FLOAT, move_speed, PROPERTY_HINT_RANGE, "0,10000,10,10");
}
