/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#include "types/array2d.hpp"

using namespace ARMORY;

template <typename T> 
void Array2D<T>::resize(index_t x, index_t y)
{
    auto _temp_vector = std::vector<T>(y); 
    _data.resize(x, _temp_vector);
}

template <typename T> 
void Array2D<T>::resize(index_t x, index_t y, const T& value)
{
    auto _temp_vector = std::vector<T>(y, value); 
    _data.resize(x, _temp_vector);
}

template <typename T> 
void Array2D<T>::resize(size2d_t s)
{
    auto _temp_vector = std::vector<T>(s.y); 
    _data.resize(s.x, _temp_vector);
}

template <typename T> 
void Array2D<T>::resize(size2d_t s, const T& value)
{
    auto _temp_vector = std::vector<T>(s.y, value); 
    _data.resize(s.x, _temp_vector);
}

template <typename T> 
Array2D<T>::size2d_t Array2D<T>::size() const
{
    auto x = _data.size();
    auto y = x > 0 ? _data[0].size() : 0;
    return {x,y};
}
template <typename T> 
Array2D<T>::index_t  Array2D<T>::columns() const
{
    return _data.size();
}

template <typename T> 
Array2D<T>::index_t  Array2D<T>::rows() const
{
    auto x = _data.size();
    return x > 0 ? _data[0].size() : 0;
}


template <typename T> 
T& Array2D<T>::at(index_t x, index_t y)
{
#if HAS_EXCEPTION
    try
    {
        return _data.at(x,y);
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_V_MSG(_data.back(), oor.what());
    }
#else
    if (x> _data.size() || y > (_data.size() > 0 ? _data[0].size() : 0)) 
    {
        return _data[x][y];
    }
    else
    {
        ERR_FAIL_V_MSG(_data.back(), "index out of bounds");
    }
#endif
}

template <typename T> 
const T& Array2D<T>::at(index_t x, index_t y) const
{
#if HAS_EXCEPTION
    try
    {
        return _data.at(x,y);
    }
    catch (std::out_of_range oor)
    {
        ERR_FAIL_V_MSG(_data.back(), oor.what());
    }
#else
    if (x> _data.size() || y > (_data.size() > 0 ? _data[0].size() : 0)) 
    {
        return _data[x][y];
    }
    else
    {
        ERR_FAIL_V_MSG(_data.back(), "index out of bounds");
    }
#endif
}

template <typename T> 
void Array2D<T>::clear()
{
    // should we clear other dimension ?
    _data.clear();
}

template <typename T> 
T& Array2D<T>::back()
{
    return _data.back().back(); 
}

template <typename T> 
const T& Array2D<T>::back() const 
{
    return _data.back().back();
}

template <typename T> 
T& Array2D<T>::front()
{
    return _data.front().front();
}

template <typename T> 
const T& Array2D<T>::front() const
{
    return _data.front().front();
}
