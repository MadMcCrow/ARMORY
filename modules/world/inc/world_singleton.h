/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_STATICS_H
#define ARMORY_WORLD_STATICS_H

// std
#include <cstdint> 
#include <random>

// godot
#include <core/object/class_db.h>
#include <core/object/ref_counted.h>

namespace armory
{

/**
 * 	@class WorldSingleton
 *  Contains functions and data for scripts and objects
 */
class WorldSingleton :  public RefCounted
{
    GDCLASS(WorldSingleton, RefCounted);
    static void _bind_methods();

public:

    WorldSingleton();
    static WorldSingleton* get_singleton();

private:

   static WorldSingleton* singleton;

    /** Random values generator - mersenne twister */ 
    std::mt19937 random_gen;

public:

    enum Direction : uint8_t
    {
        North,
        South,
        East,
        West,
        NS, // North and south are equals
        WE, // West and east are equals
        All, // All directions are the same
    };

  
    /** reset generator to get identical result */
    static void reset_gen() {get_random_gen() = std::mt19937(); }

    static std::mt19937& get_random_gen() {return get_singleton()->random_gen;}

    // random float
    static const float randf(float min = 0.f, float max = 1.f)
    {
        std:: uniform_real_distribution<> dis(min, max);
        return  dis(get_random_gen());
    };

    // random integer
    static const int randi(int min, int max)
    {
        std:: uniform_int_distribution<> dis(min, max);
        return  dis(WorldSingleton::get_random_gen());
    };

    // random boolean
    static const bool randb(float p_true)
    {
        clampf(p_true, 0.f,1.f); 
        std::discrete_distribution<> dis({1-p_true, p_true});
        return static_cast<bool>(dis(WorldSingleton::get_random_gen()));
    };





};


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

    // it's like modulo, but better 
    static constexpr int repeat(int p, int q)
    {
        return (p >= 0 ? 0 : q) + p % q; 
    }

    static constexpr float smoothstep(float edge0, float edge1, float x) 
    {
        // Scale, bias and saturate x to 0..1 range
        x = clampf((x - edge0) / (edge1 - edge0), 0.0, 1.0); 
        // Evaluate polynomial
        return x * x * (3 - 2 * x);
    }


}; // namespace armory

#endif // ! ARMORY_WORLD_FUNC_H