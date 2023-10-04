/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>
 
#ifndef ARMORY_RANDOM_H
#define ARMORY_RANDOM_H

#include "armory.hpp"

using namespace godot;

namespace ARMORY {

    /**
     * class for generating random numbers 
     * each one uses a unique generator
     * so you can have separate random number sequences
     */
    class Random : public RefCounted {
    GDCLASS(Random, RefCounted);

     public: 

        // CTR
        Random();
        ~Random();

        // init generator with seed
        void init(size_t seed);

        // quick getter
        inline unsigned int randn() const {return gen<unsigned int>();}
        inline int randi() const     {return gen<int>();}
        inline float randf() const   {return gen<float>();}
        inline double randd() const  {return gen<double>();}

    protected:
        
        // generate 64-bit of randomness.
        // this might change meaning between 
        // little and big endian platforms
        template<typename T>
        T gen() const;

    private:

        // mersenne twister
	    std::mt19937_64* _mt;
        bool _ready;
        size_t _seed;

        // Godot API :
        static void _bind_methods();
        inline void set_seed(int seed) {init(seed);}
        inline int get_seed() const    {return _seed;}
        inline int get_integer() const {return randi();}
        inline int get_float() const   {return randf();}
    };
};

#endif /* ARMORY_RANDOM_H */