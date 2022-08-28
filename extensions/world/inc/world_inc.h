/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_INC_H
#define WORLD_INC_H

#include "godot_cpp/variant/dictionary.hpp"
#define WORLD_MAX_TILE_SET 128
#define SIDES 4

/**
 * @file world_inc.h
 * @brief Contains all the includes for the world module, as well as helper functions
 */

// std c
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdint>
// std c++
#include <iostream>
#include <bitset>
#include <stack>
#include <random>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <chrono>
#include <optional> 


// godot-cpp :
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/vector3i.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/char_string.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/texture.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>


// must use godot namespace for module code to work as extension
// we could be using aliases instead, but since this code 
// is made for godot anyway, so lets just do it now
using namespace godot;

/** World is part of armory */
namespace armory {

static std::mt19937 mersene_generator;

/**
 * Collection of helper functions !
 */

// min and max values for a uint8
static constexpr const uint8_t ui8max = std::numeric_limits<uint8_t>::max();
static constexpr const uint8_t ui8min = std::numeric_limits<uint8_t>::min();

template<typename t>
static constexpr t remap( t value,t in_min,t in_max, t out_min, t out_max)
{
    return out_min + (out_max - out_min) * ((value - in_min) / (in_max - in_min));
}

template<typename t>
static constexpr t min(t a, t b)
{
    return a < b ? a : b;
}

template<typename t>
static constexpr t max(t a, t b)
{
    return a > b ? a : b;
}

// clamping
static constexpr float clampf(float a, float min, float max)
{
    return a > max ? max : (a < min ? min : a);
    //return std::min(std::max(a, min),max);
}

// 0.f<= a <= 1.f
static constexpr uint8_t touint8(float a)
{
    return static_cast<uint8_t>(clampf(a * ui8max, ui8min, ui8max));
}

// fast power because we don't care about approximations
static constexpr double fast_pow(double a, double b)
{
    // type punning could (should ?) be replaced by memcopy
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}

/**
 * natural log on [0x1.f7a5ecp-127, 0x1.fffffep127]. Maximum relative error 9.4529e-5 
 * from https://stackoverflow.com/a/39822314 answer
 */
static constexpr float faster_logf (float a)
{
    // define variables (init to 0 for constexpr)
    float i = 0, m = 0, r = 0, s = 0, t = 0;
    int e = 0;

    m = frexpf (a, &e);
    if (m < 0.666666667f) {
        m = m + m;
        e = e - 1;
    }
    i = (float)e;
    /* m in [2/3, 4/3] */
    m = m - 1.0f;
    s = m * m;
    /* Compute log1p(m) for m in [-1/3, 1/3] */
    r =             -0.130310059f;  // -0x1.0ae000p-3
    t =              0.140869141f;  //  0x1.208000p-3
    r = fmaf (r, s, -0.121483512f); // -0x1.f198b2p-4
    t = fmaf (t, s,  0.139814854f); //  0x1.1e5740p-3
    r = fmaf (r, s, -0.166846126f); // -0x1.55b36cp-3
    t = fmaf (t, s,  0.200120345f); //  0x1.99d8b2p-3
    r = fmaf (r, s, -0.249996200f); // -0x1.fffe02p-3
    r = fmaf (t, m, r);
    r = fmaf (r, m,  0.333331972f); //  0x1.5554fap-2
    r = fmaf (r, m, -0.500000000f); // -0x1.000000p-1  
    r = fmaf (r, s, m);
    r = fmaf (i,  0.693147182f, r); //  0x1.62e430p-1 // log(2)
    if (!((a > 0.0f) && (a < INFINITY))) 
    {
        r = a + a;  // silence NaNs if necessary
        if (a  < 0.0f) r = INFINITY - INFINITY; //  NaN
        if (a == 0.0f) r = -INFINITY;
    }
    return r;
}

// This is a fast approximation to log2()
// Y = C[0]*F*F*F + C[1]*F*F + C[2]*F + C[3] + E;
static constexpr float fast_log2 (float X)
{
    float Y = 1.23149591368684f;
    int E = 0;
    float F = frexpf(fabsf(X), &E);
    Y *= F;
    Y += -4.11852516267426f;
    Y *= F;
    Y += 6.02197014179219f;
    Y *= F;
    Y += -3.13396450166353f;
    Y += E;
    return Y;
}

//log10f is exactly log2(x)/log2(10.0f)
static constexpr float  fast_log10f(float x) 
{
  return  fast_log2(x)*0.3010299956639812f;
}

/** torus-world modulo-like function */
static constexpr int repeat(int p, int q)
{
    return (p >= 0 ? 0 : q) + p % q;
}

/** set the random seed for the game */
static const void set_rand_seed(size_t random_seed)
{
    mersene_generator = std::mt19937(random_seed);
};


/** generate a float between min and max (based on last set seed) */
static const float rand_float(float min, float max)
{

    std::uniform_real_distribution<float> dis(min, max);
    return  dis(mersene_generator);
};

/** generate a int between min and max (based on last set seed) */
static const int rand_int(int min, int max)
{
    std:: uniform_int_distribution<> dis(min, max);
    return  dis(mersene_generator);
};

/** generate a boolean with certain probability (based on last set seed) */
static const bool rand_bool(float true_probability)
{
    clampf(true_probability, 0.f,1.f);
    std::discrete_distribution<> dis({1-true_probability, true_probability});
    return static_cast<bool>(dis(mersene_generator));
};


static const void add_custom_project_setting(String name, Variant default_value, Variant::Type type, const PropertyHint hint, String hint_string = "")
{
    auto PS = ProjectSettings::get_singleton();
    if (!PS)
    {
        ERR_FAIL_MSG("Failed to get project settings singleton, some module initialisation order error maybe !");
        return;
    }

	if (PS->has_setting(name))
        return;

    Dictionary dict;
    dict["name"] = name;
	dict["type"] = type;
    dict["hint"] = hint;
    dict["hint_string"] = hint_string;
  
	PS->set_setting(name, default_value);
	PS->add_property_info(dict);
	PS->set_initial_value(name, default_value);
    
    // EDMSG does not exist in GDExtension
	ERR_FAIL_COND_MSG(PS->save(), "Failed to save project settings");
}


struct _Benchmark
{
    _Benchmark(String InName) : Name(InName)
    {
        begin = std::chrono::system_clock::now();
    }
    ~_Benchmark()
    {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-begin);
        //WARN_PRINT_ED( Name + " : Benchmark duration : " + itos(elapsed.count()) + "ms");
    }
private:
    std::chrono::time_point<std::chrono::system_clock> begin;
    String Name;
};

#define BENCHMARK_FUNC() \
_Benchmark benchy__FUNCTION__(__FUNCTION__);

#define BENCHMARK_SCOPE(Name) \
_Benchmark benchy#Name(#Name);

}; // namespace armory

#endif // ! WORLD_INC_H