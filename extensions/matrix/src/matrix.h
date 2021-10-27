/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <vector>
#include "matrix_interface.h"

// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace matrix
{


/**
 *	Matrix class
 *	A nice 2D array with fast access
 */
class Matrix : public MatrixInterface
{
	GDCLASS(Matrix, MatrixInterface);

public:

	Matrix();
	~Matrix();

protected:
	// godot
	static void _bind_methods();

private:

	/** the internal */
	std::vector<Variant> internal_matrix;

	void init_matrix();

	int get_internal_size() const;

public:

	/** convert 2d coordinate to unique index */
	virtual int  get_index(int x, int y) const override;

	/** getter */
	virtual Variant get(int x, int y) const override;

	/** setter */
	virtual void set(int x, int y,const Variant& value) override;

	/** init matrix after set_size */
	virtual void set_size(const Vector2i &in_size) override;

	/** min, redefined for better performance */
	virtual Variant min() const override;

	/** max, redefined for better performance */
	virtual Variant max() const override;

};

};
#endif // ! MATRIX_CLASS_H
