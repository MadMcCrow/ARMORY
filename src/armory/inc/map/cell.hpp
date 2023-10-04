/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef ARMORY_CELL_H
#define ARMORY_CELL_H

// Godot
#include "armory.hpp"

using namespace godot;

namespace ARMORY {

    /**
     *  Class to have a 2D grid
     */
    class MapCell : public RefCounted {
        GDCLASS(MapCell, RefCounted);

    public:

        // Godot-API functions 
        static void _bind_methods();
        
        GDPROPERTY(Dictionary, data);

    };
};

#endif /* ARMORY_CELL_H */
