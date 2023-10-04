/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>
 
#ifndef ARMORY_ARRAY2D_H
#define ARMORY_ARRAY2D_H

// godot-cpp
#include <godot_cpp/core/class_db.hpp>

// std
#include <vector>

// Armory
#include "macros.hpp"

using namespace godot;

namespace ARMORY {


    /**
     *  Optimised container for 2D arrays
     */
    template<typename T>
    class Array2D {

    private:

        // actual container :
        // @note: to get better perfs optimise this
        using index_t = size_t;
        std::vector<std::vector<T>> _data;

    public:

        // grow or shrink
        void resize(index_t x, index_t y);
        void resize(index_t x, index_t y, const T& value);
        
        // empty
        void clear();

        // equivalent of [][]
        T& at(index_t x, index_t y);
        const T& at(index_t x, index_t y) const;


        // first and last :
        T& back();
        const T& back() const;
        T& front();
        const T& front() const;
    };

};


#endif /* ARMORY_ARRAY2D_H */