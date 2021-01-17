/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_ACTOR_3D_H
#define ARMORY_ACTOR_3D_H

#include "scene/3d/node_3d.h" // Node godot class

/** Armory namespace */
namespace Armory {

/**
 *  Actor3D 
 *  @brief implements functions like Ready, Update, etc.
 *  all bindings are done in this class
 */
class Actor3D : public Node3D  {
    GDCLASS(Actor3D, Node3D);

public:

    // ctr
    Actor3D();

    // dstr
    ~Actor3D();



    /**
     *  ready
     *  @brief called when node is ready to start doing stuff
     *  @note  is connected via signal
     */
    virtual void ready();

    /**
     *  update
     *  @brief called each frame
     *  @param delta : deltaframe
     *  @note  is connected via _bind_methods.
     *  @todo  investigate using signals
     */
    virtual void update(float delta);

    /**
     *  update
     *  @brief called on a change in the node tree
     *  @todo  investigate using signals
     */
    virtual void tree_update();
    

     /**
     *  _bind_methods native function : expose function to GDScript
     *  @note add the function to the reflexion API
     */
    static void _bind_methods();

};

} // namespace Armory

#endif //ACTOR_3D_H
