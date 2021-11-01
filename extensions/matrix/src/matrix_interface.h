/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MATRIX_INTERFACE_CLASS_H
#define MATRIX_INTERFACE_CLASS_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/ref.hpp>

// we must use this namespace if we want to compile against godot
using namespace godot;

// make sure we do not override
namespace matrix
{


/**
 * 	@class MatrixInterface
 *	Base Matrix functions
 *	Offers function for child classes
 */
class MatrixInterface :  public RefCounted
{
    GDCLASS(MatrixInterface, RefCounted);


protected:


    /** size property */
    Vector2i size;

public:

    // do nothing here, expose only what child classes do actually need
    static void _bind_methods();

    /** convert 2d coordinate to unique index */
    virtual int get_index(int x, int y) const;
    /** vector index getter */
    inline int get_indexv(const Vector2i &vector) const
    {
        return get_index(vector.x, vector.y);
    }

    /** getter */
    virtual Variant get(int x, int y) const;
    /** vector getter variant */
    inline Variant getv(const Vector2i &vector) const
    {
        return get(vector.x, vector.y);
    }

    /** setter */
    virtual void set(int x, int y,const Variant& value);
    /** vector setter variant */
    inline void setv(const Vector2i &vector,const Variant& value)
    {
        set(vector.x, vector.y, value);
    }

    /** size getter and setter */
    virtual void set_size(const Vector2i &in_size);
    virtual Vector2i get_size() const;

    /** Get smallest variant of this matrix */
    virtual Variant min() const;

    /** Get biggest variant of this matrix */
    virtual Variant max() const;

    /** set all values between in_min and in_max */
    virtual void normalize(Variant in_min, Variant in_max);

    /** fill this matrix with linear data and dimensions */
    virtual void fill(Vector2i in_size, Array in_data);

    /** how to use image as an input */
    enum ImageInputMode : int
    {
        COLOR,
        VECTOR,
        BRIGHTNESS,
        GRAY
	};

    /** fill this matrix with an image */
    virtual void from_image(const Ref<Image>& in_image, int in_mode);

    /** retrieve this matrix as an image */
    virtual void to_image(Ref<Image> out_image) const;

    /** apply another matrix as a filter */
    virtual void apply_filter(const Ref<MatrixInterface> &in_filter);

};

};

VARIANT_ENUM_CAST(matrix::MatrixInterface, ImageInputMode);

#endif // ! MATRIX_INTERFACE_CLASS_H
