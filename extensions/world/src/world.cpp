/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "world.h"

#include <algorithm>
#include <godot_cpp/core/class_db.hpp>

using namespace world;

#define NOT_IMPLEMENTED()   std::cout << "call to not implemented function " << __FUNCTION__ << "\n";
#define MAX_OMP 6



void World::init_vector()
{
    // reserve does not create elements,  resize does.
    //internal_matrix.reserve(size.x * size.y);
    cell_vector.resize(size.x * size.y);
}


void World::_bind_methods()
{
	// Methods.
    ClassDB::bind_method(D_METHOD("generate_from_image", "image"),  &World::generate_from_image);
    ClassDB::bind_method(D_METHOD("export_to_image"),               &World::export_to_image);


	// Properties
	ADD_GROUP("World", "world_");

	// internal setup
	ADD_SUBGROUP("Generation", "generation_");

	// size
	ClassDB::bind_method(D_METHOD("get_size"), &World::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &World::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size"), "set_size", "get_size");



}

/** size getter and setter */
void World::set_size(const Vector2i &in_size)
{
    size = in_size;
    init_vector();
}

Vector2i World::get_size() const
{
    return size;
}


int World::get_index(int x, int y) const
{
    return (x % size.x) + (y % size.y) * size.x;
}

World::Cell World::get(int x, int y) const
{
   try
    {
        return cell_vector.at(get_index(x,y));
    }
   catch (std::out_of_range oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        return Cell();
    }
}

void World::set(int x, int y, const World::Cell &cell)
{
   try
    {
        cell_vector.at(get_index(x,y)) = cell;
    }
   catch (std::out_of_range oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
}



void World::generate_from_image(const Ref<Image>& in_image)
{
    if (in_image.is_null())
    {
        return;
    }

    auto image_size = in_image->get_size(); 

    // build heightmap
    std::vector<uint8_t> heightmap;
    heightmap.resize(image_size.x * image_size.y);
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int)idx / size.x;
        const int x = idx % size.x;
        Color col = in_image->get_pixel(x,y);
        // we build height based on value (luminance)
        heightmap.at(idx) = col.get_v();
    }


    // get min and max  of our height map
    auto min_max_itr = std::minmax_element(heightmap.begin(), heightmap.end());
    auto _min = *min_max_itr.first;
    auto _max = *min_max_itr.second;
    constexpr auto normalize = [](uint8_t value, uint8_t min, uint8_t max) 
    {
        constexpr auto out_min = std::numeric_limits<uint8_t>::min();
        constexpr auto out_max = std::numeric_limits<uint8_t>::max();
        return out_min + (value - min) * (out_max - out_min) / (max - min);
    };

    // build actual cell vector
    set_size(image_size);
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        cell_vector.at(idx) =  Cell(normalize(heightmap.at(idx), _min, _max));
    }
}


Ref<Image> World::export_to_image()
{
    
    Ref<Image> out_image;
    out_image.instantiate();
    out_image->create( size.x, size.y, false, Image::FORMAT_L8);
    //#pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int) idx / size.x;
        const int x = idx % size.x;
        
        Color col = Color::from_hsv(0.f, 0.f, float(get(x,y).height) / 255.f, 1.f);
        out_image->set_pixel(x,y,col);
    }
    return out_image;
}
