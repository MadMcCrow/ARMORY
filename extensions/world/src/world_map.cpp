/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_map.h"
#include "world_cell.h"
#include "world_solver.h"
#include "world_tile.h"

using namespace armory;

void WorldMap::_bind_methods(){
    // WorldMap Methods
    ClassDB::bind_method(D_METHOD("set_map_solver", "in_tile_set"), &WorldMap::set_map_solver);
    ClassDB::bind_method(D_METHOD("get_map_solver"), &WorldMap::get_map_solver);
    // Properties
    ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("WORLD", "world_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "map_solver", PROPERTY_HINT_RESOURCE_TYPE, "WorldSolver"), "set_map_solver", "get_map_solver");
}

WorldMap::WorldMap() : Node(){

}

WorldMap::~WorldMap(){
    map_solver.unref();
}

void WorldMap::set_map_solver(const Ref<WorldSolver> &in_solver){
    map_solver = in_solver;
}