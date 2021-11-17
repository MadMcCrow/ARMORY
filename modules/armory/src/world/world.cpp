/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world/world.h"

//std
#include <algorithm>
#include <cmath>
#include <random>
#include <string>

// godot
#include <core/object/class_db.h>
#include <core/error/error_macros.h>

// world
#include "world/world_func.h"

using namespace world;

#if 0	

void World::_bind_methods()
{
	// Methods.

    // Image related
    //ClassDB::bind_method(D_METHOD("generate", "seed", "sea_level"),  &World::generate);
    ClassDB::bind_method(D_METHOD("export_to_image", "image"),      &World::export_to_image);

	// Properties
	ADD_GROUP("World", "world_");
	// generation properties
	ADD_SUBGROUP("Generation", "generation_");
	// size
	ClassDB::bind_method(D_METHOD("get_size"), &World::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "in_size"), &World::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size"), "set_size", "get_size");
    // modules
    ClassDB::bind_method(D_METHOD("get_modules"), &World::get_modules);
	ClassDB::bind_method(D_METHOD("set_modules", "in_modules"), &World::set_modules);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "modules"), "set_modules", "get_modules");
}




World::World() : Node()
{
}

Dictionary World::get_modules() const
{
   return modules_dict;
}

void World::set_modules(const Dictionary& in_modules)
{
    
    modules_dict = in_modules;
/*
    // copy to vector :

    size_t count = in_modules.size();
    modules_vector.clear(); // clear set vector size at zero
    modules_vector.reserve(count);
    #pragma omp parallel for
    for (int idx = 0; idx < count; ++idx)
    {
        WorldModule mod;
        Variant def = Ref<WorldModule>(&mod);
        Variant key = idx;
        Ref<WorldModule> res = in_modules.get(key, def);
        modules_vector[idx] = *(*res);
    }
    */
}



/** size getter and setter */
void World::set_size(const Vector2i &in_size)
{
    size = in_size;
    // init_vector();
}

Vector2i World::get_size() const
{
    return size;
}

size_t World::get_index(int x, int y) const
{
    // beware negative numbers
    return repeat(x, size.x) + repeat(y, size.y) * size.x;
}

/*
const World::Cell& World::get(int x, int y) const
{
    // doing it like this would be less lines but using try/catch would yeld better performance
    // const size_t idx = get_index(x,y);
    // ERR_FAIL_INDEX_V_MSG(idx, size.x * size.y, ErrorCell, "index is out_of_range");
    // return cell_vector.at(idx);
    try
    {
        return cell_vector.at(get_index(x,y));
    }
    catch (std::out_of_range oor)
    {
        ERR_PRINT("Out of Range error");
        return ErrorCell;
    }
}

World::Cell& World::get(int x, int y)
{
    try
    {
        return cell_vector.at(get_index(x,y));
    }
    catch (std::out_of_range oor)
    {
        ERR_PRINT("Out of Range error");
        return ErrorCell;
    }
}


void World::set(int x, int y, const World::Cell &cell)
{
    // const size_t idx = get_index(x,y);
    // ERR_FAIL_INDEX_MSG(idx, size.x * size.y, "index is out_of_range");
    // cell_vector.at(idx) = cell;
    try
    {
        cell_vector.at(get_index(x,y)) = cell;
    }
    catch (std::out_of_range oor)
    {
        ERR_PRINT("Out of Range error");
    }
}
*/

int World::dist2(int ax, int ay, int bx, int by)
{
    ax = repeat(ax, size.x);
    ay = repeat(ay, size.y);
    bx = repeat(bx, size.x);
    by = repeat(by, size.y);
    return (bx-ax) + (by-ay);
}


// simple fail safe:
//ERR_FAIL_COND_MSG(min(size.x, size.y) <= 0, "Size must be a positive integer on x and y");

void World::export_to_image(Ref<Image> out_image)
{
    if (out_image.is_null())
    {
        out_image.instantiate();
    }
    // set the image
    out_image->create( size.x, size.y, false, Image::FORMAT_L8);
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y) 
    {
        for (int x = 0; x < size.x; ++x) 
        {
            /*
            float height = get(x,y).height;
            // height is between min and max, it need to be between 0 and 1 :
            float value = remap(height, -8.f, 8.f, 0.f,1.f);
            Color col = Color::from_hsv(0.f, 0.f, value, 1.f);
            out_image->set_pixel(x,y,col);
            */
        }
    }
}


#endif 0