/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MATRIX_VIEW_CLASS_H
#define MATRIX_VIEW_CLASS_H


#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>

#include "matrix_interface.h"
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
class MatrixView : public MatrixInterface
{
	GDCLASS(MatrixView, MatrixInterface);

protected:
	// godot
	static void _bind_methods();

private:

	/** position of the first sub_matrix element you look at */
	Vector2i first;

	/** the internal */
	Ref<Matrix> reference_matrix;

public:

	/**
	 * @func init_matrix
	 * initialize matrix from another matrix, a size and a corner
	 * @param main_matrix	the matrix you're reading/setting from
	 * @param in_first		the top left corner
	 * @param in_size		the size of this view
	 */
	void view(const Ref<MatrixInterface> &main_matrix, Vector2i in_first, Vector2i in_size);

	/** getter */
	virtual Variant get(int x, int y) const override;

	/** setter */
	virtual void set(int x, int y,const Variant& value) override;

	/** size */
	virtual void set_size(const Vector2i &in_size) override;

	/** first is top left - getter */
	Vector2i get_first() const;

	/** first is top left - setter */
	void set_first(const Vector2i& in_first);

};

};
#endif // ! MATRIX_VIEW_CLASS_H
