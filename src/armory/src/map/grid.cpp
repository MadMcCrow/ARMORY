/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#include "map/grid.hpp"

using namespace ARMORY;

// helper function
static int _repeat( int p , int q) {
	return ((p >= 0) ? 0 :  q) + p % q;
}

MapGrid::MapGrid(int x, int y) {
    set_grid_size(x,y);
}
MapGrid::~MapGrid() {
    _cells.clear();
    _size_x = 0;
    _size_y = 0;
}

void MapGrid::set_grid_size(int x, int y) {
    // Todo : expand or clamp instead of clear
    // empty map :
    _cells.clear();
    // update values
    _size_x = x;
    _size_y = y;
    // recreate map array:
    _cells.resize(_size_x, _size_y);
}

MapCell& MapGrid::elem_at(const int& x, const int& y) {
    return _cells.at(_loops ? _repeat(x, _size_x) : x, _loops ? _repeat(y, _size_y) : y);
}

const MapCell& MapGrid::elem_at(const int& x, const int& y) const {
    return _cells.at(_loops ? _repeat(x, _size_x) : x, _loops ? _repeat(y, _size_y) : y);
}

void MapGrid::_bind_methods() {
    BIND_GDPROPERTY(MapGrid, Vector2i, size, Variant::VECTOR2I);
    BIND_GDPROPERTY(MapGrid, bool, loops, Variant::BOOL); 
    // cell functions
    BIND_METHOD(MapGrid, get_cell);
    //BIND_METHOD_PARAMS(MapGrid, set_cell, "position", "cell")
}