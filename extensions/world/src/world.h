/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <vector>
#include <cstdint> 
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/ref.hpp>


// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace world
{



/**
 * 	@class World
 *	Base Matrix functions
 *	Offers function for child classes
 */
class World :  public RefCounted
{
    GDCLASS(World, RefCounted);

public:


    /** 
     *  @struct Cell
     *  Describe a world cell with all the necessary info layed on top
     */
    struct Cell
    {
        /** how to represent it on the map */
        uint8_t height;

        // TODO: replace this with something more sensible (smart pointer maybe ?)
        /** is there anything on top */
        //uint8_t unit_id;


        Cell(uint8_t in_height = 0) : height(in_height)
        {}
    };



private:

    /** size property */
    Vector2i size;

    /** the internal */
	std::vector<Cell> cell_vector;

    void init_vector();

protected:

    // do nothing here, expose only what child classes do actually need
    static void _bind_methods();

    /** convert 2d coordinate to unique index */
    int get_index(int x, int y) const;

    /** getter */
    Cell get(int x, int y) const;

    /** setter */
    void set(int x, int y, const Cell &cell);

public:

    /** size getter and setter */
    void set_size(const Vector2i &in_size);
    Vector2i get_size() const;

    /** fill this matrix with an image */
    virtual void generate_from_image(const Ref<Image>& in_image);

    /** retrieve this matrix as an image */
    virtual Ref<Image> export_to_image();

};

};


#endif // ! WORLD_CLASS_H
