/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include <algorithm>
#include "matrix.h"
#include <godot_cpp/core/class_db.hpp>


#define MAX_OMP 4

using namespace matrix;

Matrix::Matrix() : MatrixInterface()
{
    set_size(size);
}

Matrix::~Matrix()
{

}

void Matrix::_bind_methods() {
	// Methods.
	//ClassDB::bind_method(D_METHOD("init_matrix"),			&Matrix::init_matrix);
	ClassDB::bind_method(D_METHOD("get_index", "x", "y"),	    &Matrix::get_index);
	ClassDB::bind_method(D_METHOD("get_indexv", "coord"),	    &Matrix::get_indexv);
	ClassDB::bind_method(D_METHOD("get", "x", "y"),			    &Matrix::get);
	ClassDB::bind_method(D_METHOD("getv", "coord"), 		    &Matrix::getv);
	ClassDB::bind_method(D_METHOD("set", "x", "y", "value"),    &Matrix::set);
	ClassDB::bind_method(D_METHOD("setv", "coord", "value"),    &Matrix::setv);

	ClassDB::bind_method(D_METHOD("min"),    &Matrix::min);
    ClassDB::bind_method(D_METHOD("max"),    &Matrix::max);
    ClassDB::bind_method(D_METHOD("normalize", "min", "max"),    &Matrix::normalize);

    ClassDB::bind_method(D_METHOD("fill", "in_size", "in_data"),    &Matrix::fill);
    ClassDB::bind_method(D_METHOD("from_image", "image", "mode"),   &Matrix::from_image);
    ClassDB::bind_method(D_METHOD("to_image", "out_image"),         &Matrix::to_image);
    ClassDB::bind_method(D_METHOD("apply_filter", "filter"),        &Matrix::apply_filter);

    

	// Properties
	ADD_GROUP("Matrix", "matrix_");

	// internal setup
	ADD_SUBGROUP("Matrix size", "matrix_size_");

	// size
	ClassDB::bind_method(D_METHOD("get_size"), &Matrix::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Matrix::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "matrix_size"), "set_size", "get_size");

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


void Matrix::set_size(const Vector2i &in_size)
{
    size = in_size;
    init_matrix();
}


Variant Matrix::min() const
{
    return *std::min_element(internal_matrix.begin(), internal_matrix.end());
}

Variant Matrix::max() const
{
    return *std::max_element(internal_matrix.begin(), internal_matrix.end());
}
