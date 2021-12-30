/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_PLUGIN_H
#define ARMORY_WORLD_PLUGIN_H


// godot class
#include <editor/editor_plugin.h>

namespace armory
{
class WorldPlugin : public EditorPlugin 
{
	GDCLASS(WorldPlugin, EditorPlugin);
};
};

#endif // ARMORY_WORLD_PLUGIN_H