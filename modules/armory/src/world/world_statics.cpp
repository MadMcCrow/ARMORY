/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world/world_statics.h"

using namespace armory;

// bindings

void WorldStatics::_bind_methods()
{
    ClassDB::bind_integer_constant(get_class_static(), StringName(), north(), static_cast<uint8_t>(Direction::North));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), south(), static_cast<uint8_t>(Direction::South));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), east(),  static_cast<uint8_t>(Direction::East));
    ClassDB::bind_integer_constant(get_class_static(), StringName(), west(),  static_cast<uint8_t>(Direction::West));
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