/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_GRID_2D_H
#define ARMORY_GRID_2D_H

// Godot Includes
#include "core/templates/vector.h" // for vector container
#include "core/object/reference.h" // for reference
#include "core/math/vector2.h"     // for Point2i


// STL includes
#include <vector> // std vector, more flexible than Godot Vector
#include <memory> // weak and shared pointer, easier than godot references
#include <optional>

namespace Armory
{

/** Armory alias */
template <typename T>
using GridVector = std::vector<T>;

/** PrivateGrid2D alias for vector of vector  */
template <typename T>
using PrivateGrid2D  = GridVector<GridVector<T>>;

/** Armory alias , with "reference" aspect*/
template <typename T>
using SharedGrid2D = std::weak_ptr<PrivateGrid2D<T>>;

/** GridSize2D alias for Point2i */
using  GridSize2D = Point2i;

/**
 *  Grid 
 *  @brief 2 dimension array with sub grid capability
 *  @note the subscript are [y] [x] (outer vector is y)
 */
template <typename T>
class Grid2D : public Reference
{

private:

    /** 
     * the actual grid data, shared between grids and subgrids 
     */
    SharedGrid2D<T>  data;


    /** whether this grid has been created by us */
    bool is_data_owner;


    /** grid start (offset first element) compared to actual data */
    GridSize2D          start;

    /** dimesion of our part of the data */
    GridSize2D          dimension;

    std::optional<std::shared_ptr<PrivateGrid2D<T>>> get_data_shared()  const
    {
        if (auto sp = data.lock())
            return sp;
        return  std::nullopt;
    }

    bool data_valid() const
    {
        return  data.lock() ? true : false;
    }

 protected:

    /** 
     * at @note, this is y first
     * @todo : make data check debug only
     */
    virtual T* at(const GridSize2D & coord)
    {
         if (auto sp = get_data_shared())
        {
            PrivateGrid2D<T> * grid = sp.value().get();
            const auto sz = size();

            const int x = (coord.x + start.x) % sz.x;
            const int y = (coord.y + start.y) % sz.y;

            return &(((*grid)[y])[x]);
        }
        return nullptr;
    }
public:


    // CTR
    Grid2D(GridSize2D size = GridSize2D(1,1))
    {
       start = GridSize2D(0,0);
       data = std::make_shared<PrivateGrid2D<T>>(PrivateGrid2D<T>());
       is_data_owner = true;
       resize(size);
    }

    // CTR
    Grid2D(Grid2D<T> *parent_grid ,const GridSize2D &sub_start =  GridSize2D(0,0),const GridSize2D &sub_end =  GridSize2D(0,0)  )
    : start(sub_start)
    {
        data = parent_grid->data;
        is_data_owner = false;
        dimension = parent_grid->distance2d_to(sub_start, sub_end);
    }

    //DSTR
    virtual ~Grid2D()
    {

    }


    /** reference subscript operator */
    T& operator[] (const GridSize2D & coord)
    {
        return *at(coord);
    } 

    /** const subscript operator */
    T operator[] (const GridSize2D & coord) const
    {
        return *at(coord);
    }

    /** size gets the size of this subgrid if a subgrid, of the whole grid otherwise */
    virtual GridSize2D size() const
    {
        if (auto sp = get_data_shared())
        {
            PrivateGrid2D<T> * grid = sp.value().get();
            const int x = (*grid)[0].size();
            const int y = grid->size() ;
            const auto real_size = GridSize2D(x,y);

            if (dimension != real_size)
            {
                return dimension;
            }
            return real_size;
        }
        return GridSize2D(0,0);
    }

    /**resize the dimension if a subgrid, the whole data if the original grid */
    virtual void resize(const GridSize2D & new_size)
    {
        if (is_data_owner)
        {
            if (auto sp = get_data_shared())
            {
                PrivateGrid2D<T> * p_grid = sp.value().get();
                const constexpr auto max = [](size_t a, size_t b) -> size_t {return a > b ? a : b; };
                const size_t x = max(1, new_size.x);
                const size_t y = max(1, new_size.y);

                // resize Y first, then resize X
                p_grid->resize(y);
                for ( int idx = 0; idx < p_grid->size(); idx++)
                {
                    (*p_grid)[idx].resize(x);
                }
            }
        }
        else // not the creator of the data
        {
            dimension = new_size % Grid2D<T>::size();
        }
    }

    /** Distance between two point onm the grid */
    virtual GridSize2D distance2d_to( const GridSize2D & a, const GridSize2D & b)
    {
        auto sz = size();
        int dist_x, dist_y;
        {
            int b_x = b.x % sz.x;
            int a_x = a.x % sz.x;
            dist_x  = b_x > a_x ?  b_x - a_x : (sz.x + b_x ) - a_x;
        }
        {
            int b_y = b.y % sz.y;
            int a_y = a.y % sz.y;
            dist_y  = b_y > a_y ?  b_y - a_y : (sz.y + b_y ) - a_y;
        }

        return GridSize2D(dist_x, dist_y);
    }


};


} // namespace Armory


#endif //ARMORY_GRID_2D_H