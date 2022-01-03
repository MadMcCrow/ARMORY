/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_statics.h"

using namespace armory;

// bindings

void WorldStatics::_bind_methods()
{
    // BIND_ENUM_CONSTANT(m_constant)
	// ::ClassDB::bind_integer_constant(get_class_static(), StringName(), #m_constant, m_constant);

    //ClassDB::bind_integer_constant(get_class_static(), StringName(), north(),           static_cast<uint8_t>(Direction::North));
}

// Singleton stuff :

WorldStatics * WorldStatics::singleton;

WorldStatics::WorldStatics() : RefCounted()
{
    singleton = this;
    reset_gen();
}

WorldStatics* WorldStatics::get_singleton()
{
    return  WorldStatics::singleton;
}
