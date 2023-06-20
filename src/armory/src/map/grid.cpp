/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#include "map/grid.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace ARMORY;

// helper function
static int _repeat( int p , int q) {
	return ((p >= 0) ? 0 :  q) + p % q;
}

void MapGrid::set_grid_size(int x, int y) {
    // Todo : expand or clamp instead of clear
    // empty map :
    _cells.clear();
    // update values
    _size_x = x;
    _size_y = y;
    // recreate map array:
    _cells.resize(_size_x * _size_y);
}


int MapGrid::get_index(const int& x, const int& y) {
    if (_loop)
    {
        // beware negative numbers
        return _repeat(x, _size_x) + _repeat(y, _size_y) * _size_x;
    }
    // todo : fix the retvals
    ERR_FAIL_INDEX_V_MSG(x, _size_x, 0, "non-looping grid, requested x in excess");
    ERR_FAIL_INDEX_V_MSG(y, _size_y, 0, "non-looping grid, requested y in excess");
    return (x % _size_x) + (y % _size_y) * _size_x;
}


void MapGrid::_bind_methods() {
    BIND_GDPROPERTY(MapGrid, Vector2i, size, Variant::VECTOR2I );
}