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

    // default CTR
    World();


    /** 
     *  @struct Cell
     *  Describe a world cell with all the necessary info layed on top
     */
    struct Cell
    {
        /** how to represent it on the map */
        int8_t height;

        /** sea floor */
        static int8_t min_height;

        /** mountain tops */
        static int8_t max_height;

        /**  Things that can be added for diversity (do or do not affect gameplay) */
        enum Modifiers
        {
            none  = 0,
            rocks = 1, // on ground only, can be removed
            river = 2, // on ground only, cannot be removed
            tree  = 3, // on ground only, can be removed
            beach = 4, // ground to sea transition only
            fish  = 1  // sea only, visual only 
        };

        Cell(int8_t in_height = 0) : height(in_height)
        {}

        void set_height(int8_t in_height) { height = in_height < max_height ? (in_height < min_height ? in_height : min_height) : max_height;}

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
    const Cell& get(int x, int y) const;

    Cell& get(int x, int y);

    /** setter */
    void set(int x, int y, const Cell &cell);

    int rect_distance(int ax, int ay, int bx, int by);

public:

    /** size getter and setter */
    void set_size(const Vector2i &in_size);
    Vector2i get_size() const;

    /** generate a world based on that seed */
    void generate(int seed, float sea);

    /** retrieve this matrix as an image */
    void export_to_image(Ref<Image> out_image);

private:



};

};


#endif // ! WORLD_CLASS_H
