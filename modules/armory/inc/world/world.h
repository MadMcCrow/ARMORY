/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_CLASS_H
#define ARMORY_WORLD_CLASS_H

// std
#include <vector>
#include <cstdint>

// godot
#include "scene/main/node.h"
#include "scene/resources/texture.h"
#include "core/io/image.h"
#include "core/object/ref_counted.h"

// world
//#include "world_cell.h"
//#include "world_module.h"

class WorldCell;
class WorldModule;

namespace armory
{

/**
 * 	@class World
 *	Base Matrix functions
 *	Offers function for child classes
 */
class World :  public Node
{
    GDCLASS(World, Node);
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
     *  the final cells 
     *  @note :
     *          Also refered as "slots" during generation, a cell is the final collapsed version
     *          another way to think about it is : a slot is a collection of possible cells,
     *          and modules are set of conditions to produce a slot
     */
	std::vector<WorldCell> cell_vector;

    /**
     *  the modules to consider to produce a final map
     *  @note :
     *          Even thought they are exposed to godot, it is NOT stored as @class Array nor Dictionary,
     *          this is to avoid casting all the time.  this induce a non trivial cost for functions 
     *          @see get_modules and @see set_modules
     *  @see cell_vector
     */
	std::vector<WorldModule> modules_vector;


    
    Dictionary modules_dict;

public:

    //  setter and getter for modules
    //  we convert to array, but to avoid casting all the time, we store as std::vector 
    Dictionary get_modules() const;
    void set_modules(const Dictionary& in_modules);

    /** convert 2d coordinate to unique index */
    size_t get_index(int x, int y) const;

    /** compute squared distance between two point on the map */
    int dist2(int ax, int ay, int bx, int by);

public:

    /** size getter and setter */
    void set_size(const Vector2i &in_size);
    Vector2i get_size() const;

    /** retrieve this world as an image */
    void export_to_image(Ref<Image> out_image);

private:

};
}; // namespace armory


#endif // ! ARMORY_WORLD_CLASS_H