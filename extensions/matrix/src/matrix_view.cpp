/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix.h"
#include <godot_cpp/core/class_db.hpp>

//#include <godot_cpp/classes/global_constants.hpp>
//#include <godot_cpp/classes/label.hpp>
//#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace matrix;
using namespace std;

void MatrixView::_bind_methods() {
	// Methods.
	ClassDB::bind_method(D_METHOD("get_index", "x", "y"),	&MatrixView::get_index);
	ClassDB::bind_method(D_METHOD("get_indexv", "coord"),	&MatrixView::get_indexv);
	ClassDB::bind_method(D_METHOD("get", "x", "y"),		&MatrixView::get);
	ClassDB::bind_method(D_METHOD("getv", "coord"), 	&MatrixView::getv);
	ClassDB::bind_method(D_METHOD("set", "x", "y", "value"), 	&MatrixView::set);
	ClassDB::bind_method(D_METHOD("setv", "coord", "value"),	&MatrixView::setv);

	// Properties
	ADD_GROUP("Matrix", "matrix_");

	// internal setup
	ADD_SUBGROUP("Matrix view", "matrix_view_");

	// size
	ClassDB::bind_method(D_METHOD("get_size"), &Matrix::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Matrix::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "matrix_internal_size"), "set_size", "get_size");
}


void MatrixView::init_matrix()
{

}

int  MatrixView::get_index(int x, int y) const
{

}

int  MatrixView::get_indexv(const godot::Vector2i &vector) const
{
	return get_index(vector.x, vector.y);
}


godot::Variant MatrixView::get(int x, int y) const
{
	return
}

godot::Variant MatrixView::getv(const godot::Vector2i &vector) const
{
	return
}

void MatrixView::set(int x, int y,const godot::Variant& value)
{

}

void MatrixView::setv(const godot::Vector2i &vector,const godot::Variant& value)
{

}

void MatrixView::set_size(const godot::Vector2i &size)
{

}

godot::Vector2i MatrixView::get_size() const
{

}
