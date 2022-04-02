/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_INC_H
#define WORLD_INC_H

#include <cmath>
#include <cstdint>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

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
static constexpr t remap( t value,t InputMin,t InputMax, t OutputMin, t OutputMax)
{
    return OutputMin + (OutputMax - OutputMin) * ((value - InputMin) / (InputMax - InputMin));
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


};

#endif // ! WORLD_FUNC_H
