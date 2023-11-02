/// Copyright (c) 2023 Noé Perard-Gayot
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef ARMORY_H
#define ARMORY_H

// TODO : support msvc that do not have that extension
#define HAS_EXCEPTION __cpp_exceptions

// std
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

// exceptions
#if HAS_EXCEPTION
#include <stdexcept>
#endif

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

#endif /* ARMORY_H */