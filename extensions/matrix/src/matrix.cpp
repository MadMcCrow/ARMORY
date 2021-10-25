/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix.h"
#include <godot_cpp/core/class_db.hpp>

using namespace matrix;

Matrix::Matrix() : RefCounted()
{

}

Matrix::~Matrix()
{

}

void Matrix::_bind_methods() {
    // Methods.
    //ClassDB::bind_method(D_METHOD("init_matrix"),			&Matrix::init_matrix);
    ClassDB::bind_method(D_METHOD("get_index", "x", "y"),	&Matrix::get_index);
    ClassDB::bind_method(D_METHOD("get_indexv", "coord"),	&Matrix::get_indexv);
    ClassDB::bind_method(D_METHOD("get", "x", "y"),			&Matrix::get);
    ClassDB::bind_method(D_METHOD("getv", "coord"), 		&Matrix::getv);
    ClassDB::bind_method(D_METHOD("set", "x", "y", "value"), &Matrix::set);
    ClassDB::bind_method(D_METHOD("setv", "coord", "value"), &Matrix::setv);o

    // Properties
    ADD_GROUP("Matrix", "matrix_");

    // internal setup
    //ADD_SUBGROUP("Matrix ", "matrix_internal_");

    // size
    ClassDB::bind_method(D_METHOD("get_size"), &Matrix::get_size);
    ClassDB::bind_method(D_METHOD("set_size", "size"), &Matrix::set_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "size"), "set_size", "get_size");
}


void Matrix::init_matrix()
{
    // reserve does not create elements,  resize does.
    //internal_matrix.reserve(get_internal_size());
    internal_matrix.resize(get_internal_size());
}

int  Matrix::get_internal_size() const
{
    return size.x * size.y;
}

int  Matrix::get_index(int x, int y) const
{
    return (x % size.x) + (y % size.y) * size.x;
}

int  Matrix::get_indexv(const Vector2i &vector) const
{
    return get_index(vector.x, vector.y);
}


Variant Matrix::get(int x, int y) const
{
    try
    {
        return internal_matrix.at(get_index(x,y));
    }
   catch (std::out_of_range oor)
    {
        std::cout << "Out of Range error: " << oor.what() << '\n';
        return Variant();
    }
}

Variant Matrix::getv(const Vector2i &vector) const
{
    try
    {
        return internal_matrix.at(get_indexv(vector));
    }
    catch (std::out_of_range oor)
    {
        std::cout << "Out of Range error: " << oor.what() << '\n';
        return Variant();
    }
}

void Matrix::set(int x, int y,const Variant& value)
{
    try
    {
        internal_matrix.at(get_index(x,y)) = value;
    }
    catch (std::out_of_range oor)
    {
        std::cout << "Out of Range error: " << oor.what() << '\n';
    }

}

void Matrix::setv(const Vector2i &vector,const Variant& value)
{
    try
    {
        internal_matrix.at(get_indexv(vector)) = value;
    }
    catch (std::out_of_range oor)
    {
        std::cout << "Out of Range error: " << oor.what() << '\n';
    }
}

void Matrix::set_size(const Vector2i &in_size)
{
    size = in_size;
    init_matrix();
}

Vector2i Matrix::get_size() const
{
    return size;
}
