/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_CAMERA_MOVE_H
#define ARMORY_CAMERA_MOVE_H

#include "scene/3d/physics_body_3d.h" // KinematicBody3D
#include "core/notification_interface.h"
#include "core/input/input_event.h"
#include "static_helper.h"

/** ARMORY namespace */
namespace ARMORY {

/**
 *  CameraMove 
 *  @brief root node to move a camera around
 */
class CameraMove : public KinematicBody3D, public NotificationInterface {
    GDCLASS(CameraMove, KinematicBody3D);
    NOTIFICATIONS()

protected:
	static void _bind_methods();

public:

    // ctr
    CameraMove();

    // dstr
    ~CameraMove();

protected:

    virtual void ready() override;

    virtual void physics_process(float delta) override;

public:

    /**
     *  add_move_input
     *  @brief ask the camera to move in a direction 
     *  @param direction_local_space Direction we should move, in local space 
     *  @note  for performance rason we transform to world space only when we perform the move command
     */
    void add_move_input(const Vector3 &direction_local_space);

protected:

    /**
     *  move_speed 
     *  @brief how fast this camera moves
     */
    float move_speed = 100;
    GETSET(float, move_speed)

private: 

    Vector3 cumulative_move_input;

    Vector3 velocity;

    float camera_gravity = 100;
};

} // namespace ARMORY

#endif //ARMORY_CAMERA_MOVE_H
