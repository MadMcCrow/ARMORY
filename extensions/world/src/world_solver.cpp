/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_solver.h"

using namespace armory;

WorldSolver::WorldSolver() : RefCounted()
{
}

void WorldSolver::_bind_methods()
{
    // Methods.

    // WorldMap Methods
    ClassDB::bind_method(D_METHOD("set_seed", "in_seed"), &WorldSolver::set_seed);
    ClassDB::bind_method(D_METHOD("get_seed"), &WorldSolver::get_seed);
    ClassDB::bind_method(D_METHOD("set_size", "in_size"), &WorldSolver::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &WorldSolver::get_size);
    ClassDB::bind_method(D_METHOD("set_tile_set", "in_tile_set"), &WorldSolver::set_tile_set);
    ClassDB::bind_method(D_METHOD("get_tile_set"), &WorldSolver::get_tile_set);
    // Properties
    ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "size"), "set_size", "get_size");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tile_set_resource", PROPERTY_HINT_RESOURCE_TYPE, "WorldTileSet"), "set_tile_set", "get_tile_set");
}

