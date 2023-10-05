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

        // aliasing
        using  mersenne = std::mt19937_64;

        // CTR
        Random();
        ~Random();

        // init generator with seed
        void init(size_t seed);

        // quick getter
        inline unsigned int randn() {return gen<unsigned int>();}
        inline int randi()          {return gen<int>();}
        inline float randf()        {return gen<float>();}
        inline double randd()       {return gen<double>();}

    protected:
        
        // generate 64-bit of randomness.
        // this might change meaning between 
        // little and big endian platforms
        template<typename T>
        T gen();

    private:

        // mersenne twister
	    mersenne* _mt;
        bool _ready;
        size_t _seed;
        size_t _gen_count;
        

        // Godot API :
        static void _bind_methods();
        inline void set_seed(int seed) {init(seed);}
        inline int get_seed() const    {return _seed;}
        inline int get_integer() {return randi();}
        inline int get_float()   {return randf();}
    };
};

#endif /* ARMORY_RANDOM_H */