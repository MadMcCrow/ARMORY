/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "camera/camera_input.h"

#include "scene/3d/camera_3d.h"

#include "camera/camera_boom.h"
#include "camera/camera_move.h"
#include "core/viewport_statics.h"


using namespace ARMORY;


CameraInput::CameraInput() : Node(), NotificationInterface()
{
}

CameraInput::~CameraInput()
{
}


void CameraInput::ready()
{
    camera_move_node = Cast<CameraMove>(get_node(camera_move));
    camera_boom_node = Cast<CameraBoom>(get_node(camera_boom));
    camera_3d_node   = Cast<Camera3D>(  get_node(camera_3d)  );

    set_process(true);
    set_process_unhandled_input(true);
}

void CameraInput::process(float delta)
{
    // reset move direction and rotation to 0
    stored_move_input = Vector2(0.f,0.f);
    stored_rotation_input = 0.f;
    move_on_mouse_screen_border(delta);
}


void CameraInput::unhandled_input(const Ref<InputEvent> &p_event, bool p_local_coords)
{
    if (p_event.is_null())
        return;

    add_zoom_input(up,   p_event->get_action_strength(input_zoom_out_name));
    add_zoom_input(down, p_event->get_action_strength(input_zoom_in_name));
    add_movement_input(down,  p_event->get_action_strength(input_move_down_name)); 
    add_movement_input(up,    p_event->get_action_strength(input_move_up_name));
    add_movement_input(left,  p_event->get_action_strength(input_move_left_name));
    add_movement_input(right, p_event->get_action_strength(input_move_right_name));
    add_rotation_input(left,  p_event->get_action_strength(input_rotate_left_name)); 
    add_rotation_input(right, p_event->get_action_strength(input_rotate_right_name));

}

void CameraInput::move_on_mouse_screen_border(float delta)
{
    const Vector2 border = get_viewport_border_movement(get_viewport(), input_border_margin);
    Vector3 move_vec = Vector3(border.x, 0.f, border.y);
    if (camera_move_node != nullptr)
    {
         camera_move_node->add_move_input(move_vec * input_scale * -1 * get_movement_scale());
    }
}

float CameraInput::get_movement_scale() const
{
    if (camera_boom_node)
    {
        return camera_boom_node->get_arm_length();
    }
    return 1.f;
}


void CameraInput::add_movement_input(MoveDirection direction, float value)
{
    if (value == 0.f)
        return;

    if (camera_move_node != nullptr)
    {
        Vector3 move_ls;
        switch (direction)
        {
        case up:
            move_ls = Vector3(0.f,0.f,1.f);
            break;
        case left:
            move_ls = Vector3(-1.f,0.f,0.f);
            break;
        case down:
            move_ls = Vector3(0.f,0.f,-1.f);
            break;
        case right:
            move_ls = Vector3(1.f,0.f,0.f);
            break;
        }
        camera_move_node->add_move_input(value * move_ls * input_scale * get_movement_scale());
    }

}

void CameraInput::add_rotation_input(MoveDirection direction, float value)
{
    if (value == 0.f)
        return;

}

void CameraInput::add_zoom_input(MoveDirection direction, float value)
{
    if (value == 0.f)
        return;

    if (camera_boom_node != nullptr)
    {
        const char sign = direction == up ? 1 : direction == down ? -1 : 0;
        camera_boom_node->add_zoom_offset(value * sign * input_scale);
    }
}


void CameraInput::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_unhandled_input", "event", "in_local_coords"), &CameraInput::unhandled_input, DEFVAL(false));
    // Properties

    ADD_GROUP("Camera", "camera_");
    BIND_PROPERTY_GETSET(CameraInput, Variant::NODE_PATH, camera_move, PROPERTY_HINT_NODE_PATH_VALID_TYPES, "CameraMove");
    BIND_PROPERTY_GETSET(CameraInput, Variant::NODE_PATH, camera_boom, PROPERTY_HINT_NODE_PATH_VALID_TYPES, "CameraBoom");
    BIND_PROPERTY_GETSET(CameraInput, Variant::NODE_PATH, camera_3d,   PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Camera3D");
    ADD_GROUP("Input", "input_");
    BIND_PROPERTY_GETSET(CameraInput, Variant::VECTOR2I,    input_border_margin,     PROPERTY_HINT_RANGE, "0,20,1");
    BIND_PROPERTY_GETSET(CameraInput, Variant::FLOAT,       input_scale,             PROPERTY_HINT_RANGE, "0,20,1,1");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_zoom_in_name,      PROPERTY_HINT_NONE, "Name of zoom input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_zoom_out_name,     PROPERTY_HINT_NONE, "Name of zoom input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_rotate_left_name,  PROPERTY_HINT_NONE, "Name of rotation input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_rotate_right_name, PROPERTY_HINT_NONE, "Name of rotation input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_move_up_name,      PROPERTY_HINT_NONE, "Name of translation input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_move_down_name,    PROPERTY_HINT_NONE, "Name of translation input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_move_left_name,    PROPERTY_HINT_NONE, "Name of translation input");
    BIND_PROPERTY_GETSET(CameraInput, Variant::STRING_NAME, input_move_right_name,   PROPERTY_HINT_NONE, "Name of translation input");
}
