/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix_interface.h"
#include <godot_cpp/core/class_db.hpp>

using namespace matrix;

#define NOT_IMPLEMENTED()   std::cout << "call to not implemented function " << __FUNCTION__ << "\n";



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