/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_PLAYER_INPUT_H
#define ARMORY_PLAYER_INPUT_H

#include "scene/main/node.h" // Node godot class
#include "core/notification_interface.h"
#include "static_helper.h"

/** ARMORY namespace */
namespace ARMORY {

/**
 *  CameraMove 
 *  @brief root node to move a camera around
 */
class CameraInput : public Node, public NotificationInterface {
    GDCLASS(CameraInput, Node);
    NOTIFICATIONS();
protected:

	static void _bind_methods();

public:

    // ctr
    CameraInput();

    // dstr
    ~CameraInput();

protected:

    // NotificationInterface override
    virtual void ready() override;
    virtual void process(float delta) override;

    /** simple enum C++ only for human readable directions */
    enum MoveDirection :unsigned char
    {
        up,
        down,
        left,
        right
    };
    
public:

    /**
     *  _unhandled_input
     *  @note  is connected via _bind_methods and "set_process_unhandled_input"
     */
    virtual void unhandled_input(const Ref<InputEvent> &p_event, bool p_local_coords);

    /** increase requested input in a direction */
    void add_movement_input(MoveDirection direction);

    /** increase requested input in a direction - left or right only */
    void add_rotation_input(MoveDirection direction);

    /** increase requested input in a direction - up or down only */
    void add_zoom_input(MoveDirection direction);

    /**
     *  move_on_mouse_screen_border
     *  @brief handle movement comming from inupt on the border of the screen
     *  @param delta frame duration
     *  @note  called at process
     */
    void move_on_mouse_screen_border(float delta);

    /**
     *  get_movement_scale
     *  @brief affect how speed changes
     *  @return by how much you should multiply the movement speed
     */
    virtual float get_movement_scale() const;

protected:

    /**
     *  border_margin 
     *  @brief how many pixels are considered border (for movement detection)
     */
    Point2i input_border_margin = Point2i(10,10);
    GETSET(Point2i, input_border_margin)


    /**
     *  CameraMove 
     *  @brief the camera control Node that we should move
     */
    NodePath camera_move;
    GETSET(NodePath, camera_move)

    /**
     *  CameraMove 
     *  @brief the boom we control to zoom and dezoom
     */
    NodePath camera_boom;
    GETSET(NodePath, camera_boom)

    /**
     *  camera_3d 
     *  @brief the camera that draws our image
     */
    NodePath camera_3d;
    GETSET(NodePath, camera_3d)


    /**
     *  input_zoom_in_name 
     *  @brief the name of the zoom action input, it will affect camera boom
     */
    String input_zoom_in_name;
    GETSET(String, input_zoom_in_name)

    /**
     *  input_zoom_out_name 
     *  @brief the name of the zoom action input, it will affect camera boom
     */
    String input_zoom_out_name;
    GETSET(String, input_zoom_out_name)

    /**
     *  input_rotate_left_name 
     *  @brief the name of the rotation action input, it will affect camera move
     */
    String input_rotate_left_name;
    GETSET(String, input_rotate_left_name)

    /**
     *  input_rotate_right_name 
     *  @brief the name of the rotation action input, it will affect camera move
     */
    String input_rotate_right_name;
    GETSET(String, input_rotate_right_name)

    /**
     *  input_translation_name 
     *  @brief the name of the translation action input, it will affect camera move
     */
    String input_move_left_name;
    GETSET(String, input_move_left_name)

    /**
     *  input_move_right_name 
     *  @brief the name of the translation action input, it will affect camera move
     */
    String input_move_right_name;
    GETSET(String, input_move_right_name)

    /**
     *  input_move_up_name 
     *  @brief the name of the translation action input, it will affect camera move
     */
    String input_move_up_name;
    GETSET(String, input_move_up_name)

    /**
     *  input_move_down_name 
     *  @brief the name of the translation action input, it will affect camera move
     */
    String input_move_down_name;
    GETSET(String, input_move_down_name)

    /**
     *  input_scale 
     *  @brief how much should we scale the input
     */
    float input_scale;
    GETSET(float, input_scale)


private:

    /** pointers to camera_move from node path */
    class CameraMove* camera_move_node;

    /** pointers to camera_boom from node path */
    class CameraBoom* camera_boom_node;

    /** pointers to camera_3d from node path */
    class Camera3D  * camera_3d_node;

    /** increase requested input in a direction */
    void add_movement_input(MoveDirection direction, float value);

    /** increase requested input in a direction - left or right only */
    void add_rotation_input(MoveDirection direction, float value);

    /** increase requested input in a direction - up or down only */
    void add_zoom_input(MoveDirection direction, float value);


    /** input pressed this frame - translation */
    Vector2 stored_move_input;

    /** input pressed this frame - rotation */
    float stored_rotation_input;

};

} // namespace ARMORY

#endif //ARMORY_PLAYER_INPUT_H
