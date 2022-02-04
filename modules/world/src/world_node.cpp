/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "world_node.h"
#include "world_singleton.h"
// godot
#include <core/object/class_db.h>
#include <core/error/error_macros.h>
#include <core/math/color.h>
// std 
#include <algorithm>
#include <cmath>

using namespace armory;

void WorldNode::_bind_methods()
{
	// Methods.

    // Image related
    //ClassDB::bind_method(D_METHOD("generate", "seed", "sea_level"),  &World::generate);
    ClassDB::bind_method(D_METHOD("export_to_image", "image", "cell_size"), &WorldNode::export_to_image);

	// Properties
	ADD_GROUP("World", "world_");
	// generation properties
	ADD_SUBGROUP("Generation", "generation_");
	// size
	ClassDB::bind_method(D_METHOD("get_size"), &WorldNode::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "in_size"), &WorldNode::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size"), "set_size", "get_size");
}




WorldNode::WorldNode() : Node()
{
}

size_t WorldNode::get_index(const Vector2i& coord) const
{
    // beware negative numbers
    return repeat(coord.x, size.x) + repeat(coord.y, size.y) * size.x;
}

Vector2i WorldNode::get_coord(size_t idx) const
{
    size_t x = idx % get_size().x;
    size_t y = idx / get_size().x;
    return Vector2i(x,y);
}

Vector2i WorldNode::distance(const Vector2i& a,const Vector2i& b) const
{
    auto a_p = a - get_size();
    auto b_p = b - get_size();

    int dist_x = std::min<int>({
        std::abs(b.x   - a.x),
        std::abs(b_p.x - a.x),
        std::abs(b.x   - a_p.x),
        std::abs(b_p.x - a_p.x),
    });

    int dist_y = std::min<int>({
        std::abs(b.y   - a.y),
        std::abs(b_p.y - a.y),
        std::abs(b.y   - a_p.y),
        std::abs(b_p.y - a_p.y),
    });
    
    return Vector2i(dist_x, dist_y);
}


Ref<WorldCell> WorldNode::get(const Vector2i& coord) const
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
        return Ref<WorldCell>();
    }
}   

bool WorldNode::generate()
{
    // reset random generator
    WorldSingleton::reset_gen();

    // make a rray the correct size 
    const int sz = get_size().x * get_size().y;

    // recreate all cell objects
    for (auto cell : cell_vector)
    {
        cell.unref();
    }
    cell_vector.resize(sz);
    for (size_t idx = sz; idx --> 0;)
    {
        cell_vector[idx].instantiate();
        cell_vector[idx]->coord = get_coord(idx);
    }

    // start with elevation:
    std::vector<int8_t> elevations;
    elevations.resize(sz);

    // define voro-points
    size_t voro_count = WorldSingleton::randi(4, sz/10);
    struct voro_point
    {
        Vector2i location;
        int elevation;
    };
    std::vector<voro_point> voro_points;
    voro_points.resize(voro_count);

    // generate voro_points
    for (size_t idx = voro_count; idx --> 0;)
    {
        auto x = WorldSingleton::randi(0,get_size().x);
        auto y = WorldSingleton::randi(0,get_size().y);
        auto elevation = WorldSingleton::randi(0,get_size().y);
        voro_points[idx].location   = Vector2i(x,y);
        voro_points[idx].elevation  = elevation;
    }


    for (size_t x = get_size().x; x-->0;)
    {
        for (size_t y = get_size().y; y-->0;)
        {
            const auto coord = Vector2i(x,y);
            Vector2i min_dist = get_size(); // maxi is size
            Vector2i sec_min_dist = get_size(); // maxi is size

            voro_point *closer, *second_closer = nullptr;

            // find the two closest points
            for (auto voro : voro_points)
            {
                auto dist = distance(voro.location, coord);
                if (dist <= min_dist)
                {
                    min_dist = dist;
                    closer = &voro;
                    continue;
                }
                if (dist <= sec_min_dist)
                {
                    sec_min_dist = dist;
                    second_closer = &voro;
                    continue;
                }
            }

            // are two closer valids ?
            if (closer == nullptr || second_closer == nullptr)
            {
                // we failed
                return false;
            }

            // how many steps between our two closer
            const auto steps   = std::abs(closer->elevation - second_closer->elevation);
            const auto length  = floor(distance(closer->location, second_closer->location).length());

            // can we make a safe transition ?
            if (steps > length)
            {
                // cannot do it
                return false;
            }

            // now calculate elevation
            // A----
            //      \
            //       ------ B
            // we make a smoothstep tranition and then step it
            
            const auto dist_a = distance(closer->location, coord).length();
            const auto dist_b = distance(second_closer->location, coord).length();
            //elevations[get_index(coord)] = round(smoothstep(dist));



        }
    }




    // save elevation to cells :
    for (int idx = sz ; idx -->0;)
    {
       cell_vector[idx]->elevation = elevations[idx];
    }

    return true;
}


void WorldNode::export_to_image(Ref<Image> out_image, int cell_size)
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
    /*
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
    */
}