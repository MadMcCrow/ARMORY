/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world.h"

//std
#include <algorithm>
#include <cmath>
#include <random>
#include <string>

// godot
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>

using namespace world;

#define MAX_OMP 12


		
// min and max values for a uint8
static constexpr const uint8_t ui8max = std::numeric_limits<uint8_t>::max();
static constexpr const uint8_t ui8min = std::numeric_limits<uint8_t>::min();

template<typename t>
static constexpr t remap( t value,t InputMin,t InputMax, t OutputMin, t OutputMax)
{ 
    return OutputMin + (OutputMax - OutputMin) * ((value - InputMin) / (InputMax - InputMin));
}

template<typename t>
static constexpr t min(t a, t b)
{
    return a < b ? a : b;
}

template<typename t>
static constexpr t max(t a, t b)
{
    return a > b ? a : b;
}

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


static World::Cell ErrorCell = World::Cell();



/**
 * min and max values 
 * defined statically for now,
 * we could add a function to set it, but it would requiere making "world" a singleton
 */
int8_t World::Cell::min_height = -8;
int8_t World::Cell::max_height =  8;

World::World() : RefCounted()
{
}

void World::_bind_methods()
{
	// Methods.

    // Image related
    ClassDB::bind_method(D_METHOD("generate", "seed", "sea_level"),  &World::generate);
    ClassDB::bind_method(D_METHOD("export_to_image", "image"),      &World::export_to_image);

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
    cell_vector.clear();
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


size_t World::get_index(int x, int y) const
{
    // beware negative numbers
    const int fixed_x = x >= 0 ? x % size.x : size.x + (x % size.x);
    const int fixed_y = y >= 0 ? y % size.y : size.y + (y % size.y);
    return (fixed_x) + (fixed_y * size.x);
}

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

int World::rect_distance(int ax, int ay, int bx, int by)
{
    // make sure all coordinate are within (0->size)
    ax = ax % size.x;
    bx = bx % size.x;
    ay = ay % size.y;
    by = by % size.y;
    return std::abs(max(bx - ax, by - bx));
}

void World::generate(int seed, float sea)
{
    if (min(size.x, size.y) <= 0)
    {
        return;
    }

    std::mt19937 gen(seed);

    const auto randi = [&gen](int min, int max) -> float
    {
        std:: uniform_int_distribution<> dis(min, max);
        return  dis(gen);
    };

    const auto randb = [&gen](float p_true) -> bool
    {
        clampf(p_true, 0.f,1.f); 
        std::discrete_distribution<> dis({1-p_true, p_true});
        return static_cast<bool>(dis(gen));
    };

    // get points count
    const int points_count = randi(1,(size.x * size.y));

    // for each point , dig or build up
    for (size_t i =  points_count; i-->0;)
    {
        const uint8_t dir = randb(sea) ? -1 : 1;
        const int x_coord = randi(0, size.x -1); 
        const int y_coord = randi(0, size.y -1);
        const int range   = randi(1, min(size.x,size.y)/4);

        // for each cell in the point vicinity, set the new height
        //#pragma omp parallel for collapse(2)
        for (int y = y_coord - range; y <= y_coord + range; ++y) 
        {
            for (int x = x_coord - range; x <=x_coord + range; ++x) 
            {
                Cell& t = get(x,y);
                int8_t new_height = t.height +(dir * ( range - rect_distance(x,y, x_coord, y_coord)));
                t.set_height(new_height);
            }
        }
    }
    // do something cool ??
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
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < size.y; ++y) 
    {
        for (int x = 0; x < size.x; ++x) 
        {
            float height = get(x,y).height;
            // height is between min and max, it need to be between 0 and 1 :
            float value = remap(height, -8.f, 8.f, 0.f,1.f);
            Color col = Color::from_hsv(0.f, 0.f, value, 1.f);
            out_image->set_pixel(x,y,col);
        }
    }
}

