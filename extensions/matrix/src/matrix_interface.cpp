/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix_interface.h"
#include <godot_cpp/core/class_db.hpp>

using namespace matrix;

#define NOT_IMPLEMENTED()   std::cout << "call to not implemented function " << __FUNCTION__ << "\n";



Variant _remap( Variant value,Variant InputMin,Variant InputMax, Variant OutputMin, Variant OutputMax)
{ 
    //                                                     E
    //            ^                  A                     *            D
    //            |                  A            *        B            /           C            =   F
	// return OutputMin + (OutputMax - OutputMin) * ((value - InputMin) / (InputMax - InputMin));
    bool success = true;
    Variant A,B,C,D,E,F;
    Variant::evaluate(Variant::OP_SUBTRACT,OutputMax,OutputMin, A, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_SUBTRACT,value,InputMin, B, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_SUBTRACT,InputMax,InputMin, C, success);
     if (!success) return value;
    Variant::evaluate(Variant::OP_DIVIDE, B, C, D, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_MULTIPLY, D, A, E, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_ADD, OutputMin, E, F, success);
    if (!success) return value;
    return F;
}



void MatrixInterface::_bind_methods()
{
    BIND_VIRTUAL_METHOD(MatrixInterface, get_index);
    BIND_VIRTUAL_METHOD(MatrixInterface, get);
    BIND_VIRTUAL_METHOD(MatrixInterface, set);
}

/** size getter and setter */
void MatrixInterface::set_size(const Vector2i &in_size)
{
    size = in_size;
}

Vector2i MatrixInterface::get_size() const
{
    return size;
}


int MatrixInterface::get_index(int x, int y) const
{
    NOT_IMPLEMENTED()
    return 0;
}

Variant MatrixInterface::get(int x, int y) const
{
    NOT_IMPLEMENTED()
    return Variant();
}

void MatrixInterface::set(int x, int y,const Variant& value)
{
    NOT_IMPLEMENTED()
}

Variant MatrixInterface::min() const
{
    auto _min = get(0,0);
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            const auto _val = get(x,y);
            _min = (_val < _min) ? _val : _min;
        }
    }
    return _min;
}

Variant MatrixInterface::max() const
{
    auto _max = get(0,0);
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            const auto _val = get(x,y);
            _max = (_val < _max) ? _max : _val;
        }
    }
    return _max;
}

void MatrixInterface::normalize(Variant in_min, Variant in_max)
{
    auto _max = max();
    auto _min = min();
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            set(x,y, _remap(get(x,y), _min, _max, in_min, in_max));
        }
    }
}
  
