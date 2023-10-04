/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef ARMORY_GRID_H
#define ARMORY_GRID_H

// Armory
#include "armory.hpp"
#include "cell.hpp"
#include "types/array2d.hpp"

using namespace godot;

namespace ARMORY {

    /**
     *  @class MapGrid
     *  @brief 2D Grid to contain @see MapCell
     * 
     *  @todo  maybe change to inherit from Resource
     *  @todo  maybe use Vector2i for position
     *  @todo  maybe replace MapCell by Ref<MapCell>
     */
    class MapGrid : public RefCounted {
        GDCLASS(MapGrid, RefCounted);

    public:

        MapGrid(int x = 0, int y = 0);
        ~MapGrid();

        /** Set grid size, and update cells */
        void set_grid_size(int x, int y);

        /** get cell element at position */
        MapCell& elem_at(const int& x, const int& y);

        /** get cell element at position, const version */
        const MapCell& elem_at(const int& x, const int& y) const;

    private:

        /** size */
        int _size_x = 0;
        int _size_y = 0;

        /**
         * whether the grid loops around
         * @todo maybe we'll switch to a ENUM  for readability.
         */
        bool _loops = true;

        /** Array of cells */
        Array2D<MapCell> _cells;

    public:

        // Godot-API functions 
        static void _bind_methods();
        inline Vector2i get_size() const { return Vector2i(_size_x, _size_y); }
        inline void set_size(const Vector2i& size) { set_grid_size(size.x, size.y); }
        inline void set_loops(const bool loops) { _loops = loops;}
        inline void get_loops(const bool loops) { return _loops; }
        inline void set_cell(const Vector2i& pos, const Ref<MapCell>& cell) { elem_at(pos.x, pos.y).set_data(cell->get_data()); }
        // Godot can either accept raw pointers or refs
        inline MapCell* get_cell(const Vector2i& pos) {return &(elem_at(pos.x, pos.y)); }
    };
};

#endif /* ARMORY_GRID_H */
