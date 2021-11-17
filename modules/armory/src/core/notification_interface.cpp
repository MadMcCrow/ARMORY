/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// ARMORY includes
#include "core/notification_interface.h"
#include "static_helper.h"
// Godot includes
#include "scene/main/node.h"
#include "scene/main/scene_tree.h"
#include "scene/scene_string_names.h"

using namespace ARMORY;

Node* _get_underlying_node(NotificationInterface * interface)
{
    if (Node* ret_node = dynamic_cast<Node*>(interface))
    {
        return ret_node;
    }
    return nullptr;
}

SceneTree* _get_scene_tree(NotificationInterface * interface)
{
    if (Node* ret_node = dynamic_cast<Node*>(interface))
    {
        return ret_node->get_tree();
    }
    return nullptr;
}

NotificationInterface::NotificationInterface()
{
}

NotificationInterface::~NotificationInterface()
{
}


void NotificationInterface::_notification_call(int p_notification)
{
    switch (p_notification)
    {
        case Node::NOTIFICATION_PARENTED :
        {
            parented();
        }
        break;
        case Node::NOTIFICATION_READY    :
        {
#ifdef TOOLS_ENABLED
        Engine::get_singleton()->is_editor_hint() ? editor_ready() : ready();
#else
        ready();
#endif
        }
        break;
        case Node::NOTIFICATION_PROCESS:
        {
            if(SceneTree * tree = _get_scene_tree(this))
                process(tree->get_process_time());
        }
        break;
        case Node::NOTIFICATION_PHYSICS_PROCESS:
        {
            if(SceneTree * tree = _get_scene_tree(this))
                physics_process(tree->get_physics_process_time());
        }
        break;
        case Node::NOTIFICATION_PAUSED:
        {
            pause();
        }
        break;
        case Node::NOTIFICATION_UNPAUSED:
        {
            unpause();
        }
        break;
        default:
            break;
    }
}

