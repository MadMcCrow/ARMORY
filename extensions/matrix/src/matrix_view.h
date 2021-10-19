/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MATRIX_VIEW_CLASS_H
#define MATRIX_VIEW_CLASS_H


#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>

#include "matrix.h"


// we must use this namespace if we want to compile against godot
using namespace godot;


// make sure we do not override other namespace
namespace matrix
{

/**
 *	Matrix class
 *	A nice 2D array with fast access
 */
class MatrixView : public RefCounted {
	GDCLASS(MatrixView, RefCounted);

protected:
	// godot
	static void _bind_methods();

private:

	/** position of the first sub_matrix element you look at */
	Vector2i first;


	/** size of this matrix */
	Vector2i size;

	/** the internal */
	Ref<Matrix> reference_matrix;

	/** initialize matrix to a certain size */
	void init_matrix(const Ref<Matrix> &main_matrix, Vector2i size);

	Vector2i modulated(const Vector2i &vector) 	const;
	Vector2i clamped(const Vector2i &vector) 	const;

public:

	/** getter */
	Variant get(int x, int y) const;
	Variant getv(const Vector2i &vector) const;

	/** setter */
	void set(int x, int y,const Variant& value);
	void setv(const Vector2i &vector,const Variant& value);

	/** size */
	void set_size(const Vector2i &in_size);
	Vector2i get_size() const;

};

};
#endif // ! MATRIX_VIEW_CLASS_H
