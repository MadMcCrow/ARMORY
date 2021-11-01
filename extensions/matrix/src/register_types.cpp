/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "register_types.h"
#include <godot/gdnative_interface.h>
// Base necessary godot include
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

// matrix classes
#include "matrix.h"
#include "matrix_view.h"

using namespace godot;
using namespace matrix;

void register_matrix_types() {
	ClassDB::register_class<MatrixInterface>();
	ClassDB::register_class<Matrix>();
	ClassDB::register_class<MatrixView>();
}

void unregister_matrix_types() {}

extern "C" {

// Initialization.

GDNativeBool GDN_EXPORT matrix_library_init(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_scene_initializer(register_matrix_types);
	init_obj.register_scene_terminator(unregister_matrix_types);

	return init_obj.init();
}
}

