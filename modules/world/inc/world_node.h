/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_NODE_CLASS_H
#define ARMORY_WORLD_NODE_CLASS_H

// std
#include <vector>
#include <cstdint>
#include <optional>

// godot
#include "scene/main/node.h"
#include "scene/resources/texture.h"
#include "core/io/image.h"
#include "core/object/ref_counted.h"


namespace armory
{

class WorldCell :  public Node
{
    GDCLASS(WorldCell, Node);

public:
    Vector2i coord;
    int8_t elevation;
    uint8_t type;
    Ref<Object> top_object;

}


/**
 * 	@class World
 *	Base Matrix functions
 *	Offers function for child classes
 */
class WorldNode :  public Node
{
    GDCLASS(WorldNode, Node);
    static void _bind_methods();

public:

    // default CTR
    World();

private:

    /** 
     * size property
     * stored as a godot Vector2i directly
     */
    Vector2i size;

    /** 
     * min_elevation
     * min height of map
     */
    int8_t min_elevation;

    /** 
     * max_elevation
     * max height of map
     */
    int8_t max_elevation;

    /**
     *  the final cells 
     */
	std::vector<Ref<WorldCell>> cell_vector;

protected:


    size_t get_index(const Vector2i& coord) const;
    Vector2i get_coord(size_t idx) const;
    Vector2i distance(const Vector2i& a,const Vector2i& b) const;
    Ref<WorldCell> get(const Vector2i& coord) const;

    
public:

    // ---- begin Godot bindings  ----
    void set_size(const Vector2i &in_size)  { size = in_size;         }
    Vector2i get_size() const               { return size;            }
    void set_min_elevation(int8_t &in_min)  { min_elevation = in_min; }
    int8_t get_min_elevation() const        { return min_elevation;   }
    void set_max_elevation(int8_t &in_max)  { max_elevation = in_max; }
    int8_t get_max_elevation() const        { return max_elevation;   }
    // ---- end Godot bindings  ----

    /** 
     * Generate map 
     * @return false on failure
     */
    bool generate();

    /**
     *  retrieve this world as an image 
     *  @param [out] out_image  the resulting image
     *  @param       cell_size  the how many pixels to allocate for cells
     */
    void export_to_image(Ref<Image> out_image, int cell_size);

};
}; // namespace armory


#endif // ! ARMORY_WORLD_NODE_CLASS_H