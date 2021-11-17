/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_CAMERA_BOOM_H
#define ARMORY_CAMERA_BOOM_H

#include "scene/3d/node_3d.h" // Node godot class
#include "core/notification_interface.h"
#include "core/input/input_event.h"
#include "static_helper.h"

/** ARMORY namespace */
namespace ARMORY {

/**
 *  CameraBoom 
 *  @brief a arm to have a camera on an offset
 */
class CameraBoom : public Node3D, public NotificationInterface {
    GDCLASS(CameraBoom, Node3D);
    NOTIFICATIONS()

protected:
	static void _bind_methods();

public:

    // ctr
    CameraBoom();

    // dstr
    ~CameraBoom();

protected:

    // NotificationInterface overrides
    virtual void ready() override;
    virtual void process(float delta_time) override;

public:

    /**
     *  add_zoom_offset 
     *  @brief increase or decrease zoom
     *  @param delta how much to increase or decrease the zoom
     */
    void add_zoom_offset(float delta);


    /**
     *  get_arm_length
     *  @brief distance between camera and this node 
     *  @return the current length of the camera boom
     */
    _ALWAYS_INLINE_ float get_arm_length() const {return arm_length;}

protected:

    /**
     *  zoom_speed 
     *  @brief how fast we should transition between zoom position
     */
    float zoom_speed;
    GETSET(float, zoom_speed)

    /**
     *  zoom_min 
     *  @brief how close can we get 
     */
    float zoom_min;
    GETSET(float, zoom_min)

    /**
     *  zoom_max 
     *  @brief how far can we get 
     */
    float zoom_max;
    GETSET(float, zoom_max)

    /**
     *  zoom_max 
     *  @brief how far can we get 
     */
    float zoom_input_multiplier;
    GETSET(float, zoom_input_multiplier)


    /**
     *  arm_length_target
     *  @brief the desired length of the camera arm/boom
     *  @note editor only preview parameter
     */
    float arm_length_target;
    GET(float, arm_length_target)
#if TOOLS_ENABLED
    _ALWAYS_INLINE_ void SETTER(arm_length_target)(float in_arm_length_target)
    {
        arm_length_target = clamp(in_arm_length_target, zoom_min, zoom_max);
        if (Engine::get_singleton()->is_editor_hint())
        {
            arm_length = in_arm_length_target;
            arm_length_target = in_arm_length_target;
            update_boom();
        }
    }
#else
    SET(float, arm_length_target)
#endif

    /**
     *  circle_radius  
     *  @brief the size of the 
     *  @note custom setter allows changing the length in editor.
     *        the custom setter is not compiled on shipping binary
     */
    float circle_radius;
    GET(float, circle_radius)
#if TOOLS_ENABLED
    _ALWAYS_INLINE_ void SETTER(circle_radius)(float in_circle_radius)
    {
        circle_radius = in_circle_radius;
        if (Engine::get_singleton()->is_editor_hint())
        {
            update_boom();
        }
    }
#else
    SET(float, circle_radius)
#endif


    /**
     *  max_curve_angle_degrees  
     *  @brief we are on a circle under this limit, on the tangential line after that
     *  @note custom setter allows changing the length in editor.
     *        the custom setter is not compiled on shipping binary
     */
    float max_curve_angle_degrees;
    GET(float, max_curve_angle_degrees)
#if TOOLS_ENABLED
    _ALWAYS_INLINE_ void SETTER(max_curve_angle_degrees)(float in_max_curve_angle_degrees)
    {
        max_curve_angle_degrees = in_max_curve_angle_degrees;
        if (Engine::get_singleton()->is_editor_hint())
        {
            update_boom();
        }
    }
#else
    SET(float, max_curve_angle_degrees)
#endif




private:

    /** 
     *  arm_length_target
     *  @brief the length of the camera arm/boom
     *  not exposed to the editor
     */
    float arm_length;

    /** find position on the curve to then get position and rotation in world space */
    _FORCE_INLINE_ Vector2 get_camera_position() const
    {
            // camera path function is f(x)=If(x<Rcos(θ), R-sqrt(R^(2)-x^(2)), a x+b)
            // a = cot(θ) = 1/tan(θ)
            // b = R-((R)/(sin(θ)))
            const float t = Math::deg2rad(max_curve_angle_degrees);
            const float cost = cos(t);
            const float sint = sin(t);
            const float a = cost / sint;
            const float b = circle_radius-(circle_radius/sint);
            const auto f = [a, b, cost, this](float x) -> float {
                                                return x < circle_radius * cost ?  
                                                circle_radius-Math::sqrt(circle_radius *circle_radius -x*x) :
                                                a * x + b;
                                                };
            // we need to figure out x:
            // x=If(Distance(A,O)≥L,(sqrt(4 L^(2) R^(2)-L^(4)))/(2 R),(sqrt(a^(2) L^(2)-b^(2)+L^(2))-a b)/(a^(2)+1))
            // the distance to the shifting point is : sqrt((R cos(θ))^2 + (R - R sin(θ))^2)
            // that simplifies to R sqrt(2 - 2 sin(θ)) if R and θ are positive
            const float x =Math::sqrt(sq(circle_radius* cost) + sq(circle_radius - circle_radius * sint)) >= arm_length ?
                            Math::sqrt(4.f * sq(arm_length) * sq(circle_radius) - p4(arm_length)) / (2.f * circle_radius) :
                            (Math::sqrt(sq(a) * sq(arm_length) -sq(b) + sq(arm_length))-a * b) / ( sq(a)+1.f);
            
            // return the vector
            return Vector2(x, f(x));
    }

    /** update this node rotation and childs positions */
    void update_boom();




};

} // namespace ARMORY

#endif //ARMORY_CAMERA_BOOM_H
