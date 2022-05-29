/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_INC_H
#define WORLD_INC_H

/**
 * @file world_inc.h
 * @brief Contains all the includes for the world module, as well as helper functions
 */

// std
#include <stack>
#include <cmath>
#include <cstdint>
#include <random>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

// godot :
#include <core/typedefs.h>
#include <core/object/class_db.h>
#include <core/object/ref_counted.h>
#include <core/error/error_macros.h>
#include <core/math/color.h>
#include <core/io/resource.h>
#include <core/io/image.h>
#include <core/config/project_settings.h>
#include <scene/resources/texture.h>
#include <scene/resources/mesh.h>
#include <scene/main/node.h>

namespace armory
{


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
static const int rand_float(float min, float max)
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

	
	PropertyInfo setting_info(type, name, hint, hint_string);
  
	PS->set_setting(name, default_value);
	PS->set_custom_property_info(setting_info.name, setting_info);
	PS->set_initial_value(name, default_value);
    
	ERR_FAIL_COND_EDMSG(PS->save(), "Failed to save project settings");
}


};

#endif // ! WORLD_INC_H
