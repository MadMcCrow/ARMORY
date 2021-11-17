/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_NOTIFICATION_INTERFACE_H
#define ARMORY_NOTIFICATION_INTERFACE_H

#include "scene/main/node.h"
#include "scene/scene_string_names.h"



/**
 *  Notification macro to make classes receive notifications
 */
#define NOTIFICATIONS() \
        void _notification(int p_what){_notification_call(p_what);} 



/** ARMORY namespace */
namespace ARMORY {

/**
 *  NotificationInterface : allows making scripting in C++ 
 *  @brief implements functions like Ready, Update, etc.
 *  all bindings are done in this class, so you just need to inherit from it
 *  @todo : avoid process and physics_process unecessary calls to node tree (for deltatime)
 */
class NotificationInterface {

public:

    // ctr
    NotificationInterface();

    // dstr
    ~NotificationInterface();

//  here are the interface functions 
protected:
    /**
     *  _notification_call
     *  @brief call update functions based on notifications
     */
    virtual void _notification_call(int p_notification);


// next are the notification events you should override
// they are called via notification, and do nothing by default
// @note : maybe this could be protected ?
public:

    /**
     *  parented
     *  @brief called when node is has been added to the tree to start doing stuff
     */
    virtual void parented() {};

    /**
     *  ready
     *  @brief called when node is ready to start doing stuff
     */
    virtual void ready() {};


    /**
     *  process
     *  @brief called each frame
     *  @param delta : deltaframe
     */
    virtual void process(float delta) {};

    /**
     *  physics_process
     *  @brief called each physics step
     *  @param delta : deltatime between steps
     */
    virtual void physics_process(float delta) {};

    /**
     *  pause
     *  @brief called when game is paused
     */
    virtual void pause() {};

    /**
     *  pause
     *  @brief called when game is paused
     *  @note  is connected via notifications
     */
    virtual void unpause() {};

#ifdef TOOLS_ENABLED
    /**
     *  editor_ready
     *  @brief called when node is ready to start doing stuff, in editor
     */
    virtual void editor_ready() {};
#endif

};

} // namespace ARMORY

#endif //ARMORY_NOTIFICATION_INTERFACE_H
