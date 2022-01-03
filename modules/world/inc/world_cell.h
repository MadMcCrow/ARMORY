/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_CELL_CLASS_H
#define ARMORY_WORLD_CELL_CLASS_H

//std
#include <set>
#include <cstdint>
#include <vector>

// armory
#include "world_resource.h"

// forward declaration
class Texture2D;

// make sure we do not override
namespace armory
{

/**
 *  @class Cell
 *  Describe a world cell type with all the necessary info layed on top
 */
class Cell :  public WorldResource
{
    GDCLASS(Cell, WorldResource);
    static void _bind_methods();

public:

    Cell();

private:

    /**
     *  The cell type name, used as a tag/reference for allowed neighbours
     */
    StringName cell_type_name;

    /**
     *  The 2D image to use to draw this tile
     */
    Ref<Texture2D> tile_2d;


public:

    // getters and setters for bindings

    StringName get_cell_type() const;
    void       set_cell_type(const StringName &in_cell_type);
    
    Ref<Texture2D>  get_tile_2d() const;
    void            set_tile_2d(const  Ref<Texture2D> &in_tile_2d);

};

/** struct to allow sorting of set */
struct ltRefCell
{
    bool operator()(const Ref<Cell> &T1, const Ref<Cell> &T2) const
    {
        return (uintptr_t(T1.ptr()) <uintptr_t(T2.ptr()));
    }
};


typedef std::set<Ref<Cell>,ltRefCell> CellSet;


}; // namespace armory

#endif // ! ARMORY_WORLD_CELL_CLASS_H