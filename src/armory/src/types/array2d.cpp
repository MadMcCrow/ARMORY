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
T& Array2D<T>::at(index_t x, index_t y)
{
    return _data[x][y];
}

template <typename T> 
const T& Array2D<T>::at(index_t x, index_t y) const
{
    return _data[x][y];
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
