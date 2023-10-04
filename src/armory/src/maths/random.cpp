/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>
 
#include "maths/random.hpp"

using namespace ARMORY;


Random::Random()
{
    mt = nullptr;
    _ready = false;
}

Random::~Random()
{
    if (mt != nullptr)
    {
        delete mt;
    }
    _ready = false;
}

void Random::init(size_t seed)
{
    if (mt != nullptr)
    {
        delete mt;
    }
    mt = new mt(seed);
    _ready = (mt != nullptr);
}

template<typename T>
T Random::gen();
{
    if (_ready && mt != nullptr)
    {
        // TODO : respect endianness to get same result on any platform
		const int64_t v = (*mt)();
        T r = *(reinterpret_cast<T>(&v));
        return r;
    }
    return 0;
}

void Random::_bind_methods() {

   BIND_METHOD(Random, get_seed);
   BIND_METHOD(Random, get_integer);
   BIND_METHOD(Random, get_float);
   BIND_METHOD_PARAMS(Random, set_seed, "seed");
}