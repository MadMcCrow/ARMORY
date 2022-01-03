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

    ClassDB::bind_integer_constant(get_class_static(), StringName(), north(),           static_cast<uint8_t>(Direction::North));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), south(),           static_cast<uint8_t>(Direction::South));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), east(),            static_cast<uint8_t>(Direction::East));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), west(),            static_cast<uint8_t>(Direction::West));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), north_south(),     static_cast<uint8_t>(Direction::NS));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), west_east(),       static_cast<uint8_t>(Direction::WE));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), all_directions(),  static_cast<uint8_t>(Direction::All));
}

// Singleton stuff :

WorldStatics * WorldStatics::singleton;

WorldStatics::WorldStatics() : RefCounted()
{
    singleton = this;
}

WorldStatics* WorldStatics::get_singleton()
{
    return  WorldStatics::singleton;
}

// static values :


const StringName WorldStatics::north()
{
    return StringName("North", true);
}

const StringName WorldStatics::south()
{
    return StringName("South", true);
}

const StringName WorldStatics::east()
{
   return StringName("East", true);
}

const StringName WorldStatics::west()
{
    return StringName("West", true);
}

const StringName WorldStatics::north_south()
{
    return StringName("NS", true);
}
const StringName WorldStatics::west_east()
{
    return StringName("WE", true);
}
const StringName WorldStatics::all_directions()
{
    return StringName("AllDirection", true);
}