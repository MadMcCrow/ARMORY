/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix_view.h"
#include <godot_cpp/core/class_db.hpp>


using namespace matrix;

static constexpr int _clamp(int a, int min, int max)
{
	const int t = a < min ? min : a;
 	return t > max ? max : t;
}

static Vector2i _modv(const Vector2i &vector,  Vector2i size)
{
	return Vector2i(vector.x % size.x, vector.y % size.y);
}

static Vector2i _clampv(const Vector2i &vector,  Vector2i size)
{
	return Vector2i(_clamp(vector.x, 0, size.x), _clamp(vector.y, 0, size.y));
}

void MatrixView::_bind_methods() {

	// Methods.
	ClassDB::bind_method(D_METHOD("view", "matrix", "first", "size"), &MatrixView::view);
	ClassDB::bind_method(D_METHOD("get", "x", "y"),		&MatrixView::get);
	ClassDB::bind_method(D_METHOD("getv", "coord"), 	&MatrixView::getv);
	ClassDB::bind_method(D_METHOD("set", "x", "y", "value"), 	&MatrixView::set);
	ClassDB::bind_method(D_METHOD("setv", "coord", "value"),	&MatrixView::setv);

	ClassDB::bind_method(D_METHOD("min"),    &MatrixView::min);
    ClassDB::bind_method(D_METHOD("max"),    &MatrixView::max);
    ClassDB::bind_method(D_METHOD("normalize", "min", "max"),    &MatrixView::normalize);

	// Properties
	ADD_GROUP("Matrix", "matrix_");

	ADD_SUBGROUP("Matrix View", "matrix_view_");

	// size
	ClassDB::bind_method(D_METHOD("get_size"), &MatrixView::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &MatrixView::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "matrix_size"), "set_size", "get_size");

	// first
	ClassDB::bind_method(D_METHOD("get_first"), &MatrixView::get_first);
	ClassDB::bind_method(D_METHOD("set_first", "first"), &MatrixView::set_first);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "view_first"), "set_first", "get_first");
}

void MatrixView::view(const Ref<MatrixInterface> &main_matrix, Vector2i in_first, Vector2i in_size)
{
	reference_matrix = main_matrix;
	first = in_first;
	set_size(size);
}

Variant MatrixView::get(int x, int y) const
{
	return reference_matrix->getv(_modv(Vector2i(x,y), size) + first);
}

void MatrixView::set(int x, int y,const Variant& value)
{
	reference_matrix->setv(_modv(Vector2i(x,y), size) + first, value);
}

void MatrixView::set_size(const Vector2i &in_size)
{
	const auto maxsize = reference_matrix->get_size();
	size = Vector2i(_clamp(in_size.x, 0, maxsize.x), _clamp(in_size.y, 0, maxsize.y));
}

Vector2i MatrixView::get_first() const
{
	return first;
}

void MatrixView::set_first(const Vector2i& in_first)
{
	first = in_first;
}