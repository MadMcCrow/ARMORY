/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef GRID_H
#define GRID_H

// Godot Includes
#include "core/object/reference.h"
//#include "core/templates/vector.h" // Godot Array
#include <vector> // std vector 


namespace Armory
{

// forward declaration
template <typename T, size_t N>
class Grid;


/** GridSize @see Grid.  */
template<size_t N>
class  GridSize
{
private:

    // actual data
    size_t d[N] =  {0};

public:

    // itr begin
    size_t* begin() noexcept 
    {
        return &d[0];
    }   

    //itr end
    size_t* end() noexcept
    {
         return &d[N-1];
    }

    //itr end const
    size_t last() const noexcept
    {
         return d[N-1];
    }


    // subscript
    constexpr size_t operator[] (size_t idx) const
    {
        if (idx < N)
            return d[idx];
        else return last();
    } 

    // subscript
    constexpr size_t& operator[] (size_t idx)
    {
     if (idx < N)
            return d[idx];
        else return *end();
    } 


    // param ctr
    GridSize( size_t c[N])
    {
        // check for zero dimension
        static_assert(N>0);
        std::copy(c, c+(N-1), d);
    }

    // dft ctr
    GridSize()
    {
        // check for zero dimension
        static_assert(N>0);
    }

    constexpr inline unsigned long num() const 
    {
        unsigned long n = 1;
        for(  size_t dim = 0 ; dim <N ; dim++)
        {
            n *= dim;
        }
        return n;
    }

    // Ordering operator
    bool operator<(const GridSize<N> &other)
    {
        bool retval = true;
        for (size_t n  = 0 ; n < N ; n++)
        {
            if (d[n] >= other[n])
            {
                retval = false;
                break;
            }
        }
        return retval;
    }

    // Ordering operator
    bool operator>(const GridSize<N> &other)
    {
        bool retval = true;
        for (size_t n  = 0 ; n < N ; n++)
        {
            if (d[n] < other[n])
            {
                retval = false;
                break;
            }
        }
        return retval;
    }


};



/** Inner grid @see Grid.  */
template <typename T, size_t N>
class GridPrivate : public Reference
{
    friend class Grid<T,N>;

    protected :

    /** 
     * Array stored as 1D
     * @note  std vector allows for reserve, begin, end, simple  cross platform storage and multithreading
     */
    std::vector<T> data;
    
    /** 
     * Actual size of the array 
     */
    GridSize<N> dimension;

public: 

    /** 
     *  CTR
     *  this create a new array
     */
    GridPrivate(const GridSize<N> &dim = GridSize<N>(), T* raw_data = nullptr) : dimension(dim)
    {
        static_assert(N >= 1);
        data = std::vector<T>();
        auto num = dim.num();
        
        // std array :
        data.resize(num);
        if(raw_data != nullptr)
        {
           std::copy_n(raw_data, num, data.begin());
        }
    }


    /** 
     *  fixed_pos
     *  make sure position is within range
     */
    constexpr  GridSize<N> fixed_pos( const GridSize<N> &pos) 
    {
        GridSize<N> retval;
        // fix each direction
        for( size_t d = 0; d < N; d++ )
            retval[d] = pos[d] % dimension[d];
        return retval;
    }

    T  &at(const  GridSize<N> &pos)
    {
        GridSize<N> pos_fixed = fixed_pos(pos);
        size_t idx = pos_fixed[0];
        for( size_t d = 1; d < N; d++ )
        {
            idx += pos_fixed[d] * dimension[d - 1];
        }
        return &data[idx];
    }

    /** 
     *  from_index
     *  find coordinates from index
     *  works no matter the N dimensions
     */
    static constexpr GridSize<N> from_index( const size_t &idx, const  GridSize<N> &res) 
    {
        GridSize<N> retval;
        // calculate first two dimension as they are easy
        retval [0] = idx % res[0];
        retval [1] = ((idx - retval[0] ) / res[0]) % res[1];


        if constexpr( N > 2) // cpp 17 static if ;)
        {

            auto prod_dim = res[0]; // D1
            auto sub_idx =  retval[0]; // (x)

            // Z equation (3D) is : z = ( ( Index - y * D1 - x ) / (D1 * D2) ) % D3; 
            for( size_t d = 2; d < N; d++ )
            {
                sub_idx  += retval[d-1] * prod_dim;
                // starts at res[1] * res[0]
                prod_dim *= res[d-1]; 
                //xn = ( ( Index - Index( x1, ..., x{n-1} ) ) / Product( D1, ..., D{N-1} ) ) % Dn
                retval[d] = ((index - sub_idx)/prod_dim) % res[d];
            }
        }
        // end of static if
           
        return retval;
    }

    /** 
     *  get_index
     *  find index from coordinate
     *  works no matter the N dimensions
     */
    static constexpr size_t get_index( const  GridSize<N> &coord, const  GridSize<N> &res) 
    {
        size_t retval = coord[0] % res[0];
        size_t dim_mult = 1;
        for (size_t d = 1; d< N;  d++ )
        {
            dim_mult *= res[d - 1];
            retval += coord[d] * dim_mult;
        }
        return retval;
    }


    /** 
     *  resize
     *  find coordinates from indexE
     */
    constexpr void resize (GridSize<N> &new_res)
    {
        auto num = data.size();
        auto new_num = new_res.num();
        std::vector<T> new_data;
        new_data.reserve(new_num);
        // for each index check if in array and remove it / move it to a new array
        #pragma omp for // parrallel
        for (size_t idx = 0; idx< data.size(); idx++ )
        {
            auto new_coord = from_index(idx, dimension);
            if (new_coord < new_res)
            {
                new_data[get_index(new_coord, new_res)] = data[idx];
            }
        }
    }

};


/**
 *  Grid 
 *  @brief N dimension array with sub grid capability
 */
template <typename T, size_t N>
class Grid {

private: 
    /** Grid actual data */
    Ref<GridPrivate<T,N>> inner_grid;

    /** actual grid dimesion */
    GridSize<N> dimension;

    /** actual grid start */
    GridSize<N> start;

protected:

    // ctr for subgrid
    Grid( GridSize<N> res, GridSize<N> sub_start, Ref<GridPrivate<T,N>> inner) :
    dimension(res), start(sub_start), inner_grid(inner)
    {

    }

public: 

    // ctr
    Grid(  GridSize<N> res, T* raw_data = nullptr) : 
    dimension(res), start(0)
    {
        inner_grid.instance();
    }

    /** @brief item getter - copy */
    T at(const GridSize<N> &pos) const
    {
        return inner_grid->at(pos);
    }

    /** @brief item getter - reference */
    T& at(const GridSize<N> &pos)
    {
        return inner_grid->at(pos);
    }

    /** @brief item setter */
    void set(const  GridSize<N> &pos, const T &value)
    {
        inner_grid->at(pos) = value;
    }

    Grid<T,N> subgrid(const GridSize<N>& start,const GridSize<N>& end)
    {
        GridSize<N> res;
        for (size_t n; n<N; n++)
        {
            auto s =  (start[n] % dimension[n]);
            auto e =  (end[n] & dimension[n]);
            if (start[n] < end[n])
            {
                res[n] = e - s ;
            }
            else
            {
                res[n] = dimension[n] - s + e;
            }
            
        }
        return subgrid_size(start,res);
    }


    Grid<T,N> subgrid_size(const GridSize<N>& start,const GridSize<N>& res)
    {
        return Grid( res, start, inner_grid);
    }


    // subscript operator overload
    inline T& operator[] (GridSize<N> &pos) { return at(pos); }


    /**
     *  resize grid 
     *  @warning this is slow
     */
    void resize (GridSize<N> &new_res)
    {
        dimension = new_res;
        inner_grid->resize(new_res);
    }

}; // class grid


} // namespace Armory

#endif //GRID_H
