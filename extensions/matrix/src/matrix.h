/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <godot_cpp/classes/reference.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <vector>


// make sure we do not override
namespace matrix
{


/**
 *	Matrix class
 *	A nice 2D array with fast access
 */
class Matrix : public Reference {
	GDCLASS(Matrix, Reference);

public:

	Matrix();
	~Matrix();

protected:
	// godot
	static void _bind_methods();

private:

	/** size of this vector */
	godot::Vector2i size;

	/** the internal */
	std::vector<godot::Variant> internal_matrix;

	void init_matrix();

	int get_internal_size() const;

public:

	/** convert 2d coordinate to unique index */
	int  get_index(int x, int y) const;
	int  get_indexv(const godot::Vector2i &vector) const;

	/** getter */
	godot::Variant get(int x, int y) const;
	godot::Variant getv(const godot::Vector2i &vector) const;

	/** setter */
	void set(int x, int y,const godot::Variant& value);
	void setv(const godot::Vector2i &vector,const godot::Variant& value);

	/** size */
	void set_size(const godot::Vector2i &in_size);
	godot::Vector2i get_size() const;


};

};
#endif // ! MATRIX_CLASS_H
