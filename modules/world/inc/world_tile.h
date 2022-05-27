/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_TILE_H
#define WORLD_TILE_H


// world
#include "world_inc.h"


// we must use this namespace if we want to compile against godot
using namespace godot;


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

    // default CTR
    WorldTile() 
    : Resource()
    {}


    /** create a rotated copy (Clockwise) */
    Ref<WorldTile> rotate() const;

private:

    /** border codes */
    String left;
    String right;
    String up;
    String down;

    /** probability weight*/
    float weight;

    /** mesh to use to draw in 3d world */
    Ref<Mesh> tile_3d;

    /** mesh to use to draw in 2d world */
    Ref<Texture> tile_2d;


public:

    /**
     * @brief check for compatibility, does not check for rotation
     * @return true     if in this configuration it is possible, false otherwise 
     */
    bool is_compatible(const Ref<WorldTile> &left_tile, const Ref<WorldTile> &right_tile, const Ref<WorldTile> &up_tile, const Ref<WorldTile> &down_tile) const;

    //<GDScript interface>

    /** getter for @see border codes */
    _FORCE_INLINE_ String get_left() const  {return left.camelcase_to_underscore();}
    _FORCE_INLINE_ String get_right() const {return right.camelcase_to_underscore();}
    _FORCE_INLINE_ String get_up() const    {return up.camelcase_to_underscore();}
    _FORCE_INLINE_ String get_down() const  {return down.camelcase_to_underscore();}

    /** setter for @see border codes */
    _FORCE_INLINE_ void set_left(const String &in_left)   {left = in_left;}
    _FORCE_INLINE_ void set_right(const String &in_right) {right = in_right;}
    _FORCE_INLINE_ void set_up(const String &in_up)       {up = in_up;}
    _FORCE_INLINE_ void set_down(const String &in_down)   {down = in_down;}

    /** setter for @see weight */
    _FORCE_INLINE_ void set_weight(const float& in_weight) {weight = in_weight;}

    /** getter for @see {weight */
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
}; // namespace armory

#endif // ! WORLD_TILE_H
