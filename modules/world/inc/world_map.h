/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

// world
#include "world_inc.h"
#include "world_tile_set.h"


// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace armory
{

// forward declaration :
class WorldTile;
class WorldCell;


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

    // error message GODOT function
    virtual TypedArray<String> get_configuration_warnings() const override;

private:

    /** size property (stored as a godot Vector2i directly) */
    Vector2i size;

    /** the tile set we'll use for the map */
    Ref<WorldTileSet> tile_set_resource;    

    /** the generated tile_set for generation */
	std::vector<Ref<WorldTile>> gen_tile_set;

    /** total weight of gen_tile_set */
    float total_weight;

    /** the cells generated */
	std::vector<WorldCell> cell_vector;

    /** the seed you requested */
    size_t seed;

protected:

    void generate_tile_set();

    /** core of wfc loop */
    void iterate_wfc();

    /** propagate the changes made in a collapse event */
    void propagate_change(int x, int y);

    /** collapse a cell */
    void collapse(int x, int y);

    /** is there a final valid solution ? */
    bool is_collapsed() const;

    /** get cell entropy ( ie. found how many tiles this could be) */
    float get_cell_entropy(int x, int y) const;

    /** based on tile weights, recalculate for each possible tile the probability for the cell */ 
    std::vector<float> get_cell_normalized_weights(int x, int y) const;

    /** distance  between to cell */
    virtual float distance(int ax, int ay, int bx, int by) const;

    /** convert 2d coordinate to unique index for accessing @see cell_vector*/
    size_t get_index(const int &x,const int &y) const;

    /** get stored value at coordinate, with extra safety */
    const WorldCell& get_cell(const int &x, const int &y) const;
    WorldCell&       get_cell(const int &x, const int &y);

    /** godot vector2i versions to help with conversions, inline for performance */
    _ALWAYS_INLINE_ const WorldCell& get_cell(const Vector2i& in_coord) const {return get_cell(in_coord.coord[0], in_coord.coord[1]);}
    _ALWAYS_INLINE_ WorldCell&       get_cell(const Vector2i& in_coord)       {return get_cell(in_coord.coord[0], in_coord.coord[1]);}

    /** set Cell of cell */
    virtual void set_cell(const int &x, const int &y, const WorldCell &in_cell);

public:

    //<GDScript interface>

    /**  set all values of cell_vector to zero */
    void init_cells();

    /** generate cells based on last set seed and size */
    void generate_cells();

    /** setter for @see tile_set_resource */
    void set_tile_set(const Ref<WorldTileSet>& in_tile_set) {tile_set_resource = in_tile_set;}

    /** setter for @see seed */
    void set_seed(const int& in_seed) {seed = in_seed;}

    /** setter for @see size */
    void set_size(const Vector2i& in_size) {size = in_size;}

    /** getter for @see tile_set_resource */
    Ref<WorldTileSet> get_tile_set() const {return tile_set_resource;}

    /** getter for @see seed */
    int get_seed() const {return seed;}

    /** getter for @see size */
    const Vector2i& get_size() const {return size;}

    /** convert to godot image */
    void export_to_image(Ref<Image> out_image, int tile_size);


    //<\GDScript interface>
};
}; // namespace armory

#endif // ! WORLD_CLASS_H
