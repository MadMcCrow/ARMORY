/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "register_types.h"
#include <godot/gdnative_interface.h>
// Base necessary godot include
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

// world classes
#include "world.h"

using namespace godot;
using namespace world;

void register_world_types() {
	ClassDB::register_class<World>();
}

void unregister_world_types() {}

extern "C" {

// Initialization.

GDNativeBool GDN_EXPORT world_library_init(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_scene_initializer(register_world_types);
	init_obj.register_scene_terminator(unregister_world_types);

	return init_obj.init();
}
}

