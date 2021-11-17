/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_VIEWPORT_STATICS_H
#define ARMORY_VIEWPORT_STATICS_H

#include "scene/main/viewport.h"

/** ARMORY namespace */
namespace ARMORY {

/**
 *  get_border_movement
 *  @return 2D vector of camera movement, in screen space
 */
_ALWAYS_INLINE_ Vector2 get_viewport_border_movement(Viewport * viewport , const Vector2 &border_margin)
{
    const Vector2 view_size = viewport->get_camera_rect_size();
    const Vector2 mouse_pos = viewport->get_mouse_position();
    
    Vector2 retval = Vector2();
    if (mouse_pos.x < border_margin.x)
    {
        const float dist = (border_margin.x - mouse_pos.x) / border_margin.x ;
        retval.x = - 1.f *  dist*dist;
    }
    else if (mouse_pos.x > view_size.x - border_margin.x)
    {
        const float dist = (border_margin.x - (view_size.x - mouse_pos.x)) / border_margin.x ;
        retval.x = 1.f *  dist*dist;
    }
    if (mouse_pos.y < border_margin.y)
    {
        const float dist = (border_margin.y - mouse_pos.y) / border_margin.y ;
        retval.y = -1.f * dist*dist;
    }
    else if (mouse_pos.y > view_size.y - border_margin.y)
    {
        const float dist = (border_margin.y - (view_size.y - mouse_pos.y)) / border_margin.y ;
        retval.y = 1.f *  dist*dist;
    }
    return retval;
}


} // namespace ARMORY

#endif //ARMORY_VIEWPORT_STATICS_H
