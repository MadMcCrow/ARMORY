/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef ARMORY_GRID_H
#define ARMORY_GRID_H

// Godot
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

// Armory
#include "macros.hpp"
#include "cell.hpp"

using namespace godot;

namespace ARMORY {

    /**
     *  Class to have a 2D grid
     */
    class MapGrid : public RefCounted {
        GDCLASS(MapGrid, RefCounted);

    public:

        MapGrid() {}
        virtual ~MapGrid() {}

        // Set grid size, and update cells
        void set_grid_size(int x, int y);

    protected:

        // turn a 2d position into an index
        int get_index(const int& x, const int& y);

    private:

        // size
        int _size_x = 0;
        int _size_y = 0;

        // whether the grid loops around
        // maybe we'll switch to a ENUM 
        // for readability.
        bool _loop = false;

        // Actual array
        std::vector<MapCell> _cells;

    public:

        // Godot-API functions 
        static void _bind_methods();
        inline Vector2i get_size() const               { return Vector2i(_size_x, _size_y); }
        inline void     set_size(const Vector2i& size) { set_grid_size(size.x, size.y); }
    };
};

#endif /* ARMORY_GRID_H */
