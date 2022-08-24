/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

// world
#include "world_inc.h"
#include "world_tile_set.h"

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

    /** size property (stored as a godot Vector3i directly) */
    Vector3i size;

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
    void set_size(const Vector3i& in_size) {size = in_size;}

    /** getter for @see tile_set_resource */
    Ref<WorldTileSet> get_tile_set() const {return tile_set_resource;}

    /** getter for @see seed */
    int get_seed() const {return seed;}

    /** getter for @see size */
    const Vector3i& get_size() const {return size;}

    /** convert to godot image */
    void export_to_image(Ref<Image> out_image, int tile_size);


    //<\GDScript interface>
};
}; // namespace armory

#endif // ! WORLD_CLASS_H
