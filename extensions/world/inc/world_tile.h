/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_TILE_H
#define WORLD_TILE_H


// world
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/packed_string_array.hpp"
#include "world_inc.h"
#include <cstdint>




// make sure we do not override
namespace armory
{

/**
 *  @class WorldTile
 *  defines a type of ground
 */
class WorldTile :  public Resource
{
    GDCLASS(WorldTile, Resource);
    static void _bind_methods();

public:

    /**
     * @brief Shapes that can be tiled
     * @see https://en.wikipedia.org/wiki/Euclidean_tilings_by_convex_regular_polygons
     */
    enum TileableShapes  : uint8_t{
		Triangle = 3,
        Square   = 4,
        Hexagon  = 6
	};

    // default CTR
    WorldTile(): Resource(){}

	virtual void reload_from_file();


    /** create a rotated copy (Clockwise) */
    Ref<WorldTile> rotate() const;
    
private:

    /** Shape of that tile */
    TileableShapes shape;

    /**
     * @brief list of values allowed on sides
     * @note Sides are in clockwise order
     */
    std::vector<CharString> borders;

    /** probability weight*/
    float weight;

    /** mesh to use to draw in 3d world */
    Ref<Mesh> tile_3d;

    /** mesh to use to draw in 2d world */
    Ref<Texture> tile_2d;


public:

    //<GDScript interface>
    /** setter for @see borders */
    void set_borders(const PackedStringArray& in_borders);

    /** getter for @see borders */
    PackedStringArray get_borders();

    /** setter for @see shape */
    _FORCE_INLINE_ void set_shape(const TileableShapes& in_shape) {shape = in_shape; borders.resize(shape);}

    /** getter for @see shape */
    _FORCE_INLINE_ TileableShapes get_shape() {return shape;}

    /** setter for @see weight */
    _FORCE_INLINE_ void set_weight(const float& in_weight) {weight = in_weight;}

    /** getter for @see weight */
    _FORCE_INLINE_ float get_weight() const { return weight;}

    /** setter for @see tile_3d */
    _FORCE_INLINE_ void set_tile_3d(const Ref<Mesh>& in_tile_3d) {tile_3d = in_tile_3d;}

    /** getter for @see tile_3d */
    _FORCE_INLINE_ Ref<Mesh> get_tile_3d() const { return tile_3d;}

    /** setter for @see tile_3d */
    _FORCE_INLINE_ void set_tile_2d(const Ref<Texture>& in_tile_2d) {tile_2d = in_tile_2d;}

    /** getter for @see tile_3d */
    _FORCE_INLINE_ Ref<Texture> get_tile_2d() const { return tile_2d;}

    //<\GDScript interface>
};
};
// namespace armory
VARIANT_ENUM_CAST(armory::WorldTile, TileableShapes);

#endif // ! WORLD_TILE_H
