/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <vector>

// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace matrix
{


/**
 *	Matrix class
 *	A nice 2D array with fast access
 */
class Matrix : public RefCounted {
	GDCLASS(Matrix, RefCounted);

public:

	Matrix();
	~Matrix();

protected:
	// godot
	static void _bind_methods();

private:

	/** size of this vector */
	Vector2i size;

	/** the internal */
	std::vector<Variant> internal_matrix;

	void init_matrix();

	int get_internal_size() const;

public:

	/** convert 2d coordinate to unique index */
	int  get_index(int x, int y) const;
	int  get_indexv(const Vector2i &vector) const;

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
#endif // ! MATRIX_CLASS_H
