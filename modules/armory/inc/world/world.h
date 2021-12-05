/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_CLASS_H
#define ARMORY_WORLD_CLASS_H

// std
#include <vector>
#include <set>
#include <cstdint>

// godot
#include "scene/main/node.h"
#include "scene/resources/texture.h"
#include "core/io/image.h"
#include "core/object/ref_counted.h"

// world
#include "world/world_cell.h"
#include "world/world_module.h"


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

    /** Struct for possible cells */
    struct WorldSlot
    {
        /** the various possibilities for this cell */
        std::vector<Ref<WorldCell>> possibilities;

        bool is_collapsed() const {return possibilities.size() <= 1;}

        WorldSlot(std::initializer_list<Ref<WorldCell>> cell_list) 
        : possibilities(cell_list)
        {
        }
    };

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
	std::vector<WorldSlot> cell_vector;

    /**
     *  the modules to consider to produce a final map
     *  @note :
     *          Even thought they are exposed to godot, it is NOT stored as @class Array nor Dictionary,
     *          this is to avoid casting all the time.  this induce a non trivial cost for functions 
     *          @see get_modules and @see set_modules
     *  @see cell_vector
     */
	std::set<Ref<WorldModule>> modules_vector;


protected:

    size_t get_index(Vector2i coord) const;
    WorldSlot& get(Vector2i coord);
    const WorldSlot& get(Vector2i coord) const;

    
public:

    /** size getter and setter */
    void set_size(const Vector2i &in_size);
    Vector2i get_size() const;





    /** Generate map */
    bool generate();

    /**
     *  retrieve this world as an image 
     *  @param [out] out_image  the resulting image
     *  @param       cell_size  the how many pixels to allocate for cells
     */
    void export_to_image(Ref<Image> out_image, int cell_size);

private:

    /** get all possible cells this world can produce */
	std::set<Ref<WorldCell>> get_possible_cells() const;

    /** get a random module out of a sub-set of modules */
    Ref<WorldModule> get_random_module(std::set<Ref<WorldModule>> compatible_modules) const;

    /** get all modules compatible with a given slot */
    std::set<Ref<WorldModule>> get_compatible_modules(const Vector2i& coord) const;

};
}; // namespace armory


#endif // ! ARMORY_WORLD_CLASS_H