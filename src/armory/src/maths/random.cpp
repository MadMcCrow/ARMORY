/// Copyright (c) 2023 Noé Perard-Gayot MadMcCrow
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>
 
#include "maths/random.hpp"

using namespace ARMORY;

Random::Random()
{
    _mt = nullptr;
    _ready = false;
}

Random::~Random()
{
    if (_mt != nullptr)
    {
        delete _mt;
    }
    _ready = false;
}

void Random::init(size_t seed)
{
    if (_mt != nullptr)
    {
        delete _mt;
    }
    _mt = new mersenne(seed);
    _ready = (_mt != nullptr);
    _gen_count = 0;
}

template<typename T>
T Random::gen()
{
    if (_ready && _mt != nullptr)
    {
        // TODO : respect endianness to get same result on any platform
		int64_t v = (*_mt)();
        T r = *(reinterpret_cast<T*>(&v));
        _gen_count++;
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