/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow , Udit Parmar
/// this is a port of the original work by Udit Parmar at https://github.com/udit/poisson-disc-sampling
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>
 
#ifndef ARMORY_POISSON_H
#define ARMORY_POISSON_H

// Armory
#include "armory.hpp"
#include "types/array2d.hpp"

using namespace godot;

namespace ARMORY {

    /**
     *  Poisson Disc Sampling
     *  Class to have a generator
     *  We derive from refCounted because it's the smallest registerable class
     */
    class Poisson : public RefCounted {
    GDCLASS(Poisson, RefCounted);

    private:  

        // properties :
        int _seed;         // the seed for the random generator
        int _number;      // number of points to generate
        float _radius;   // radius - minimum distance between points

        // generated points
        std::vector<Vector2> _points;

        // Generate base function
        void generate();

        // Godot-API functions 
        static void _bind_methods();
        static TypedArray<Vector2> generate_vectors(int number, int seed , float radius);
        static TypedArray<Vector2i> generate_points(int number, int seed , int radius, Vector2i size);

    };

};


#endif /* ARMORY_POISSON_H */