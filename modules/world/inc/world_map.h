/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

// std
#include <vector>
#include <cstdint>

// godot-cpp
#include "scene/main/node.h"
#include "core/io/image.h"
#include "core/object/ref_counted.h"

// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace armory
{

/**
 * 	@class WorldMap
 *	Base Matrix functions
 *	Offers function for child classes
 */
class WorldMap :  public Node
{
    GDCLASS(WorldMap, Node);
    static void _bind_methods();

public:

    // default CTR
    WorldMap();

    /** how to represent it on the map */
    enum Cell : uint16_t
    {
        // base height
        min          = 0x00,   // min. for iteration
        deep_sea     = 0x00,   // sea visual only
        sea          = 0x01,   // sea visual only
        shoreline    = 0x02,   // sea visual only
        land         = 0x05,   // sea transition
        plain        = 0x06,   // level 0
        mound        = 0x07,   // level 1
        hill         = 0x09,   // level 2
        mountain     = 0x0a,   // blocks land unit
        mountain_top = 0x0b,   // blocks planes
        max          = 0x0b,   // max, for iteration

        // modifiers
        sea_oil      = 0x10,   // on deep sea, spawns a offshore platform building
        beach        = 0x15,   // sea transition, allows unloading
        river        = 0x25,   // spawns on level 1 goes to sea
        hill_tree    = 0x19,  // prevents building, stops vehicules
        hill_rock    = 0x29,  // prevents building, does not stop tanks
        ore_mine     = 0x39,  // on hills, spawns a ore mine building

        // other
        error        = 0xff,  // error value, something went wrong, out of bound
    };

private:

    /** size property (stored as a godot Vector2i directly) */
    Vector2i size;

    /** the final cells */
	std::vector<Cell> cell_vector;

    /** the seed you requested */
    size_t seed;


protected:

    /** default voronoi implementation */
    virtual void generate_voronoi();

    /** distance implementation for voronoi */
    virtual float distance(int ax, int ay, int bx, int by) const;


    /** convert 2d coordinate to unique index for accessing @see cell_vector*/
    size_t get_index(int x, int y) const;

    /** get stored value at coordinate, with extra safety */
    const Cell& get_cell(size_t x, size_t y) const;
    Cell&       get_cell(size_t x, size_t y);

    /** set Cell of cell */
    virtual void set_cell(size_t x, size_t y, const WorldMap::Cell &in_cell);

public:

    //<GDScript interface>

    /**  set all values of cell_vector to zero */
    void init_cells();

    /** generate cells based on last set seed and size */
    void generate_cells();

    /** clean cells to respect rules */
    void clean_cells();

    /** setter for @see seed */
    void set_seed(const int& in_seed) {seed = in_seed;}

    /** setter for @see size */
    void set_size(const Vector2i& in_size) {size = in_size;}

    /** getter for @see size */
    const Vector2i& get_size() const {return size;}

    /** getter for @see seed */
    int get_seed() const {return seed;}

    /** convert to godot image */
    void export_to_image(Ref<Image> out_image);

    //<\GDScript interface>
};
}; // namespace armory

VARIANT_ENUM_CAST(armory::WorldMap::Cell);

#endif // ! WORLD_CLASS_H
