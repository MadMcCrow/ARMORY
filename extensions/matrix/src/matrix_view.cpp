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

void MatrixView::_bind_methods() {
	// Methods.
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


void MatrixView::init_matrix(const Ref<Matrix> &main_matrix, Vector2i size)
{
	reference_matrix = main_matrix;
	set_size(size);
}

Vector2i MatrixView::modulated(const Vector2i &vector) const
{
	return Vector2i(vector.x % size.x, vector.y % size.y);
}

Vector2i MatrixView::clamped(const Vector2i &vector) const
{
	return Vector2i(_clamp(vector.x, 0, size.x), _clamp(vector.y, 0, size.y));
}

Variant MatrixView::get(int x, int y) const
{
	return getv(Vector2i(x,y));
}

Variant MatrixView::getv(const Vector2i &vector) const
{
	return reference_matrix->getv(modulated(vector) + first);
}

void MatrixView::set(int x, int y,const Variant& value)
{
	setv(Vector2i(x,y), value);
}

void MatrixView::setv(const Vector2i &vector,const Variant& value)
{
	reference_matrix->setv(modulated(vector) + first, value);
}

void MatrixView::set_size(const Vector2i &in_size)
{
	const auto maxsize = reference_matrix->get_size();
	size = Vector2i(_clamp(in_size.x, 0, maxsize.x), _clamp(in_size.y, 0, maxsize.y));
}

Vector2i MatrixView::get_size() const
{
	return size;
}
