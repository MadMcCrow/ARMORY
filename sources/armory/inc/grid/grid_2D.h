/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef GRID_2D_H
#define GRID_2D_H

// Godot Includes
#include "core/templates/vector.h" // for vector container
#include "core/object/reference.h" // for reference
#include "core/math/vector2.h"     // for Point2i


namespace Armory
{
 /** forward declaration */
template <typename T>
class SubGrid2D;

/** GridSize2D alias for Point2i  */
using GridSize2D = Point2i;

/** PrivateGrid2D alias for vector of vector  */
template <typename T>
using PrivateGrid2D = Vector<Vector<T>> ; 

/**
 *  Grid 
 *  @brief 2 dimension array with sub grid capability
 *  @note the subscript are [y] [x] (outer vector is y)
 */
template <typename T>
class Grid2D : public Reference
{
friend class SubGrid2D<T>;

private:

    /** pointer to the actual data */
    PrivateGrid2D<T> *  data;

 protected:

    /** 
     * at @note, this is y first
     * @todo : make data check debug only
     */
    virtual T* at(const GridSize2D & coord)
    {
        if(data == nullptr)
            return nullptr;
        
        const auto sz = size();

        // maybe we can merge those statement ?
        const int x = coord.x % sz.x;
        const int y = coord.y % sz.y;

        return (data[y])[x];
    }
public:


    // CTR
    Grid2D(GridSize2D size = GridSize2D(1,1))
    {
        data = new PrivateGrid2D<T>();

    }

    //DSTR
    ~Grid2D()
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
        int x = data->operator[](0).size();
        int y = data->size() ;
        return GridSize2D(x,y);
    }

    /**resize the subgrid if a subgrid, the whole data if the original grid */
    virtual void resize(const GridSize2D & new_size)
    {
        // assert(data)
        const constexpr auto max = [](size_t a, size_t b) -> size_t {return a > b ? a : b; };
        const size_t x = max(1, new_size.x);
        const size_t y = max(1, new_size.y);

        // resize Y first, then resize X
        data->resize(y);
        for ( int idx = 0; idx < data->size(); idx++)
        {
            data[idx]->resize(y);
        }
    }


};


template <typename T>
class SubGrid2D : Grid2D<T>
{

friend class Grid2D<T>;

protected:

    SubGrid2D(PrivateGrid2D<T> *parent) : 
    {
        data = parent;
    }

private:

    /** grid start (offset first element) */
    GridSize2D          start;

    /** dimesion (max value of the array) */
    GridSize2D          dimension;

public :

    /** 
     * at @note, this is y first
     * @todo : make data check debug only
     */
    virtual T* at(const GridSize2D & coord)
    {
        if(data == nullptr)
            return nullptr;
            
        const int x = (coord.x % dimension.x) + (start.x% dimension.x);
        const int y = (coord.y % dimension.y) + (start.y% dimension.y);

        return (data[y])[x];
    }

    virtual GridSize2D size() const override
    {   
        return dimension - start;
    }


    /**resize only the subgrid */
    virtual void resize(const GridSize2D & new_size) override
    {
        dimension = new_size % Grid2D<T>::size();
    }
};


} // namespace Armory


#endif //GRID_2D_H