/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "world.h"

#include <algorithm>
#include <cmath>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>

using namespace world;

#define MAX_OMP 12

// min and max values for a uint8
static constexpr const uint8_t ui8max = std::numeric_limits<uint8_t>::max();
static constexpr const uint8_t ui8min = std::numeric_limits<uint8_t>::min();

// clamping
static constexpr float clampf(float a, float min, float max)
{
    return a > max ? max : (a < min ? min : a);
    //return std::min(std::max(a, min),max);
}

// 0.f<= a <= 1.f
static constexpr uint8_t touint8(float a)
{
    return static_cast<uint8_t>(clampf(a * ui8max, ui8min, ui8max));
}

// fast power because we don't care about approximations
static constexpr double fast_pow(double a, double b) 
{
    // type punning could (should ?) be replaced by memcopy
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}

void World::_bind_methods()
{
	// Methods.

    // Image related
    ClassDB::bind_method(D_METHOD("generate_from_image", "image"),  &World::generate_from_image);
    ClassDB::bind_method(D_METHOD("export_to_image", "image"),      &World::export_to_image);

    // level generation steps 
    ClassDB::bind_method(D_METHOD("level", "ratio"), &World::level);
    ClassDB::bind_method(D_METHOD("steps", "count"), &World::steps);

	// Properties
	ADD_GROUP("World", "world_");
	// generation properties
	ADD_SUBGROUP("Generation", "generation_");
	// size
	ClassDB::bind_method(D_METHOD("get_size"), &World::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &World::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size"), "set_size", "get_size");
}

void World::init_vector()
{
    // reserve does not create elements,  resize does.
    //internal_matrix.reserve(size.x * size.y);
    cell_vector.resize(size.x * size.y);
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
        ERR_PRINT("Out of Range error");
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
        ERR_PRINT("Out of Range error");
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
        try
        {
            heightmap.at(idx) = touint8(col.get_v());
        }
        catch (std::out_of_range oor)
        {
            ERR_PRINT("Out of Range error");
        }
    }        constexpr auto ui8max = std::numeric_limits<uint8_t>::max();
    WARN_PRINT( "done getting heightmap");

    // get min and max  of our height map
    auto min_max_itr = std::minmax_element(heightmap.begin(), heightmap.end());
    auto _min = *min_max_itr.first;
    auto _max = *min_max_itr.second;
    constexpr auto normalize = [](uint8_t value, uint8_t min, uint8_t max) 
    {
        return ui8min + (value - min) * (ui8max - ui8min) / (max - min);
    };

    // build actual cell vector
    set_size(image_size);
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        try
        {
            cell_vector.at(idx) =  Cell(normalize(heightmap.at(idx), _min, _max));
        }
        catch (std::out_of_range oor)
        {
            ERR_PRINT("Out of Range error");
        }
    }
    WARN_PRINT( "done building map");

}


void World::export_to_image(Ref<Image> out_image)
{
    if (out_image.is_null())
    {
        out_image.instantiate();
    }

    // set the image
    out_image->create( size.x, size.y, false, Image::FORMAT_L8);

    // OMP might cause issues here
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int) idx / size.x;
        const int x = idx % size.x;
        Color col = Color::from_hsv(0.f, 0.f, float(get(x,y).height) / 255.f, 1.f);
        out_image->set_pixel(x,y,col);
    }
}


void World::level(float ratio)
{
    constexpr auto level_func = [](float x , float n)
    {
        const float sx = (x * 2 ) - 1;
        const bool neg = sx < 0; 
        return ((((neg ? -1 : 1) * fast_pow((neg ? -sx : sx) ,2 * n + 1))+1)/2);
    };

    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        try
        {
            uint8_t &height = cell_vector.at(idx).height;
            float h = level_func(float(height) /255.f, ratio);
            height = touint8(h);
        }
        catch (std::out_of_range oor)
        {
            ERR_PRINT("Out of Range error");
        }
    }
}


void World::steps(int count)
{
    constexpr auto step_func = [](float x, int c)
    {
        return (std::round(x * c) / static_cast<float>(c)); 
    };

    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        try
        {
            uint8_t &height = cell_vector.at(idx).height;
            float h = step_func(float(height) / 255.f, count);
            height = touint8(h);
        }
        catch (std::out_of_range oor)
        {
            ERR_PRINT("Out of Range error");
        }
    }
}
