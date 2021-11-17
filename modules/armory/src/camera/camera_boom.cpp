/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "camera/camera_boom.h"
using namespace ARMORY;


CameraBoom::CameraBoom() : Node3D(), NotificationInterface()
{
}

CameraBoom::~CameraBoom()
{
}

void CameraBoom::ready()
{
    set_process(true);
    arm_length_target= clamp(arm_length_target, zoom_min, zoom_max);
    arm_length =  clamp(arm_length_target, zoom_min, zoom_max);
    update_boom();
}

void CameraBoom::process(float delta)
{
    // lerp is a + t * (b - a)
    if (arm_length_target != arm_length)
    {
        arm_length = lerp(zoom_speed * delta, arm_length, arm_length_target);
        update_boom();
    }
}

void CameraBoom::add_zoom_offset(float delta)
{
    arm_length_target = clamp(arm_length_target + (delta * zoom_input_multiplier), zoom_min, zoom_max);
}

void CameraBoom::update_boom()
{
    // get info :
    Vector2 camera_location = get_camera_position();
    
    const float angle = camera_location.angle();
    const float length = camera_location.length();

    // we choose x as rotation and z as translation
    // set rotation on us
    set_rotation(Vector3(angle + M_PI ,0.f, M_PI) );
    // and translation on childs
    for (int c = get_child_count() -1 ; c>=0; c--)
    {
        if (Node3D* child = Cast<Node3D>(get_child(c)))
        {
            child->set_translation(Vector3(0.f,0.f,length));
        }
    }
}

void CameraBoom::_bind_methods()
{
    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, arm_length_target,         PROPERTY_HINT_RANGE,      "1,200,1,1");
    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, circle_radius,             PROPERTY_HINT_RANGE,      "1,200,1,1");
    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, max_curve_angle_degrees,   PROPERTY_HINT_RANGE,      "1,90,1,1");

    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, zoom_speed, PROPERTY_HINT_RANGE,  "0,200,10,1");
    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, zoom_min,   PROPERTY_HINT_RANGE,  "0.1,200,1,1");
    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, zoom_max,   PROPERTY_HINT_RANGE,  "0.1,200,10,1");

    BIND_PROPERTY_GETSET(CameraBoom, Variant::FLOAT, zoom_input_multiplier,   PROPERTY_HINT_RANGE,  "1,10,1,1");
}