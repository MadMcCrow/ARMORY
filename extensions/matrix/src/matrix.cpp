/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix.h"
#include <godot_cpp/core/class_db.hpp>

//#include <godot_cpp/classes/global_constants.hpp>
//#include <godot_cpp/classes/label.hpp>
//#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace matrix;
using namespace std;

Matrix::Matrix() : Reference()
{

}

Matrix::~Matrix()
{

}

void Matrix::_bind_methods() {
	// Methods.
	ClassDB::bind_method(D_METHOD("init_matrix"),	&Matrix::init_matrix);
	ClassDB::bind_method(D_METHOD("get_index", "x", "y"),	&Matrix::get_index);
	ClassDB::bind_method(D_METHOD("get_indexv", "coord"),	&Matrix::get_indexv);
	ClassDB::bind_method(D_METHOD("get", "x", "y"),		&Matrix::get);
	ClassDB::bind_method(D_METHOD("getv", "coord"), 	&Matrix::getv);
	ClassDB::bind_method(D_METHOD("set", "x", "y", "value"), 	&Matrix::set);
	ClassDB::bind_method(D_METHOD("setv", "coord", "value"),	&Matrix::setv);

	// Properties
	ADD_GROUP("Matrix", "matrix_");

	// internal setup
	//ADD_SUBGROUP("Matrix ", "matrix_internal_");

	// size
	ClassDB::bind_method(D_METHOD("get_size"), &Matrix::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Matrix::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "matrix_internal_size"), "set_size", "get_size");
}


void Matrix::init_matrix()
{
	internal_matrix.reserve(get_internal_size());
}

int  Matrix::get_internal_size() const
{
	return size.x * size*y;
}

int  Matrix::get_index(int x, int y) const
{
	return (x % size.x) + (y % size.y) * size.x;
}

int  Matrix::get_indexv(const godot::Vector2i &vector) const
{
	return get_index(vector.x, vector.y);
}


godot::Variant Matrix::get(int x, int y) const
{
	return internal_matrix[get_index(x,y)];
}

godot::Variant Matrix::getv(const godot::Vector2i &vector) const
{
	return internal_matrix[get_indexv(vector)];
}

void Matrix::set(int x, int y,const godot::Variant& value)
{
internal_matrix[get_index(x,y)] = value;
}

void Matrix::setv(const godot::Vector2i &vector,const godot::Variant& value)
{
	internal_matrix[get_indexv(vector)] = value;
}

void Matrix::set_size(const godot::Vector2i &in_size)
{
	size = in_size;
	init_matrix();
}

godot::Vector2i Matrix::get_size() const
{
	return size;
}
