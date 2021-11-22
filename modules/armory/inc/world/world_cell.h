/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_CELL_CLASS_H
#define ARMORY_WORLD_CELL_CLASS_H

//std
#include <cstdint> 
#include <vector>

// godot
#include "core/object/class_db.h"
#include "core/io/resource.h"
#include "core/io/image.h"

// make sure we do not override
namespace armory
{

/**
 *  @class Cell
 *  Describe a world cell type with all the necessary info layed on top
 */
class WorldCell :  public Resource
{
    GDCLASS(WorldCell, Resource);
    static void _bind_methods();

public:

    WorldCell();

private:

    /**
     *  The cell type name, used as a tag/reference for allowed neighbours
     */
    StringName cell_type_name;

    /**
     *  The 2D image to use to draw this tile
     */
    Ref<Image> tile_2d;

    /**
     * Types of cells allowed on directions : top, down, left and right 
     */
    StringName north;
    StringName south;
    StringName east;
    StringName west;

protected:

    // getters and setters for bindings

    StringName get_cell_type() const;
    void       set_cell_type(const StringName &in_cell_type);

    Dictionary get_allowed_neighbours() const;
    void       set_allowed_neighbours(const Dictionary &neighbours);

    Ref<Image> get_tile_2d() const;
    void       set_tile_2d(const  Ref<Image> &in_tile_2d);

};

}; // namespace armory

#endif // ! ARMORY_WORLD_CELL_CLASS_H
