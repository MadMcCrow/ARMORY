/// Copyright (c) 2023 Noé Perard-Gayot
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef ARMORY_H
#define ARMORY_H

// std
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

// x86 SIMD intrinsics (for SSE)
#if __SSE__
#include <immintrin.h>
#endif

// Godot
#include <godot_cpp/core/math.hpp>                 // godot math functions
#include <godot_cpp/core/class_db.hpp>             // necessary to have godot classes
#include <godot_cpp/classes/ref_counted.hpp>       // ref counted objects
#include <godot_cpp/variant/utility_functions.hpp> // errors, etc

//armory
#include "macros.hpp"   // macros for faster godot/armory dev


// TODO : move to maths/sqrt
// fast 
namespace ARMORY {
inline float fsqrt(float x) {
    #if __SSE__ // use SSE
    float out = 0;
    __m128 in = _mm_load_ss( &x );
   _mm_store_ss( &out, _mm_mul_ss( in, _mm_rsqrt_ss( in ) ) );
   // compiles to movss, movaps, rsqrtss, mulss, movss
   return out;
   #else // Carmack's magick trick
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
    #endif
}
};

#endif /* ARMORY_H */