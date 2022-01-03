/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world.h"

// godot
#include <core/object/class_db.h>
#include <core/error/error_macros.h>
#include <core/math/color.h>

// world
#include "world_statics.h"

using namespace armory;

World::WorldSlot ErrorSlot;

void World::_bind_methods()
{
	// Methods.

    // Image related
    //ClassDB::bind_method(D_METHOD("generate", "seed", "sea_level"),  &World::generate);
    ClassDB::bind_method(D_METHOD("export_to_image", "image", "cell_size"), &World::export_to_image);

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

Array World::get_modules() const
{
    Array ret_val;
    size_t count = modules_set.size();
    ret_val.resize(count);
    for (auto module_itr : modules_set)
    {
        ret_val.append(module_itr);
    }
    return ret_val;
}

void World::set_modules(const Array& in_modules)
{
    // copy to vector :
    size_t count = in_modules.size();
    for (int idx = 0; idx < count; ++idx)
    {
        Ref<Module> ref = cast_to<Module>(in_modules.get(idx).get_validated_object());
        modules_set.emplace(ref);
    }
}

void World::set_size(const Vector2i &in_size)
{
    size = in_size;
    // init_vector();
}

Vector2i World::get_size() const
{
    return size;
}

size_t World::get_index(Vector2i coord) const
{
    // beware negative numbers
    return repeat(coord.x, size.x) + repeat(coord.y, size.y) * size.x;
}


const World::WorldSlot& World::get(Vector2i coord) const
{
    // doing it like this would be less lines but using try/catch would yeld better performance
    // const size_t idx = get_index(x,y);
    // ERR_FAIL_INDEX_V_MSG(idx, size.x * size.y, ErrorCell, "index is out_of_range");
    // return cell_vector.at(idx);
    try
    {
        return cell_vector.at(get_index(coord));
    }
    catch (std::out_of_range oor)
    {
        ERR_PRINT("Out of Range error");
        return ErrorSlot;
    }
}   

World::WorldSlot& World::get(Vector2i coord)
{
    try
    {
        return cell_vector.at(get_index(coord));
    }
    catch (std::out_of_range oor)
    {
        ERR_PRINT("Out of Range error");
        return ErrorSlot;
    }
}


bool World::generate()
{
    // get tile list in modules : (std::set)
    const auto possibilities = get_possible_cells();
 
    // reset random generator
    WorldStatics::reset_gen();

    // make a rray the correct size 
    const int sz = get_size().x * get_size().y;
    cell_vector.resize(sz, WorldSlot(possibilities)); // all Slot aloready have their possibilities set

   

    // pick a module by probability

    // pick a cell , pick a module, pick a cell from that module
    const int first_cell = randi(0, sz);
    cell_vector.at(first_cell);

    const int first_module = randi(0, modules_set.size());

    // collapse
    // watch the cell nearby : 
    // find the modules they could belong to and collapse if possible

    //repeat

    // possibilities : 
    // 1) success or error everything is collapsed -> return (true|false)
    // 2) too many possibilities : pick at random  -> collapse to a possible module
}

/*
int World::dist2(int ax, int ay, int bx, int by)
{
    ax = repeat(ax, size.x);
    ay = repeat(ay, size.y);
    bx = repeat(bx, size.x);
    by = repeat(by, size.y);
    return (bx-ax) + (by-ay);
}
*/

void World::export_to_image(Ref<Image> out_image, int cell_size)
{
    if (out_image.is_null())
    {
        out_image.instantiate();
    }
    // set the image
    out_image->create( size.x * cell_size, size.y * cell_size, false, Image::FORMAT_RGB8);

    // empty image :
    Ref<Image> empty_tile_image;
    empty_tile_image.instantiate();
    empty_tile_image->create(cell_size, cell_size, false, Image::FORMAT_RGB8);
    empty_tile_image->fill(Color(.5, .5, .5, .5));

    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y) 
    {
        for (int x = 0; x < size.x; ++x) 
        {
            const auto coord = Vector2i(x,y);
            const auto cell = get(coord).get_collapsed();
            Ref<Image> cell_image;
            if (cell.is_valid())
            {
                const auto cell_text = (*cell)->get_tile_2d();
                if (cell_text.is_valid())
                {
                    auto cell_image = (*cell)->get_tile_2d()->get_image();
                    cell_image->resize(cell_size,cell_size, Image::INTERPOLATE_NEAREST);
                } 
            }
            if (cell_image.is_null())
            {
                cell_image = empty_tile_image;
            }

            
            out_image->blit_rect(cell_image, Rect2(0,0,cell_size,cell_size),Vector2i(x*cell_size, y*cell_size));
        }
    }
}

CellSet World::get_possible_cells() const
{
    CellSet ret_val;
    for (auto mod_itr : modules_set)
    {
        ret_val.merge(mod_itr->get_world_cells());
    }
    return ret_val;
}

std::set<Ref<Module>> World::get_compatible_modules(const Vector2i& coord) const
{
    // for each module, find cells that correspond to our cell, and then check neighbours
    const WorldSlot& RefSlot = get(coord);

    for (auto itr : modules_set)
    {
        //
        //for (module)

        // TODO : continue here !
    }

}