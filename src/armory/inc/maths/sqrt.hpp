/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>
 
#ifndef ARMORY_SQRT_H
#define ARMORY_SQRT_H

#include "armory.hpp"


// TODO : godot class for exposing to GDScript
namespace ARMORY {

    /// The fastest square root approximation we could do
    inline float fsqrt(float x) {
    #if __SSE__ // use SSE
        float out = 0;
        __m128 in = _mm_load_ss( &x );
    _mm_store_ss( &out, _mm_mul_ss( in, _mm_rsqrt_ss( in ) ) );
        // compiles to movss, movaps, rsqrtss, mulss, movss
    return out;
    #else
        return fast_inverse_sqrt(x);
    #endif
    }

    /// Carmack's magick trick
    inline float fast_inverse_sqrt(float x)
    {
        float xhalf = 0.5f*x;
        int i = *(int*)&x;
        i = 0x5f3759df - (i>>1);
        x = *(float*)&i;
        x = x*(1.5f - xhalf*x*x);
        return x;
    }
};