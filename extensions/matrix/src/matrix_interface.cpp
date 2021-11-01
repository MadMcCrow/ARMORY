/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "matrix_interface.h"
#include <godot_cpp/core/class_db.hpp>

using namespace matrix;

#define NOT_IMPLEMENTED()   std::cout << "call to not implemented function " << __FUNCTION__ << "\n";
#define MAX_OMP 6


Variant _remap( Variant value,Variant InputMin,Variant InputMax, Variant OutputMin, Variant OutputMax)
{ 
    //                                                     E
    //            ^                  A                     *            D
    //            |                  A            *        B            /           C            =   F
	// return OutputMin + (OutputMax - OutputMin) * ((value - InputMin) / (InputMax - InputMin));
    bool success = true;
    Variant A,B,C,D,E,F;
    Variant::evaluate(Variant::OP_SUBTRACT,OutputMax,OutputMin, A, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_SUBTRACT,value,InputMin, B, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_SUBTRACT,InputMax,InputMin, C, success);
     if (!success) return value;
    Variant::evaluate(Variant::OP_DIVIDE, B, C, D, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_MULTIPLY, D, A, E, success);
    if (!success) return value;
    Variant::evaluate(Variant::OP_ADD, OutputMin, E, F, success);
    if (!success) return value;
    return F;
}



void MatrixInterface::_bind_methods()
{
    BIND_VIRTUAL_METHOD(MatrixInterface, get_index);
    BIND_VIRTUAL_METHOD(MatrixInterface, get);
    BIND_VIRTUAL_METHOD(MatrixInterface, set);

    BIND_ENUM_CONSTANT(COLOR);
	BIND_ENUM_CONSTANT(VECTOR);
    BIND_ENUM_CONSTANT(BRIGHTNESS);
	BIND_ENUM_CONSTANT(GRAY);
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

Variant MatrixInterface::min() const
{
    auto _min = get(0,0);
    //#pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        int y = (int)idx / size.x;
        int x = idx % size.x;
        const auto _val = get(x,y);
        //#pragma omp critical
        {
            _min = (_val < _min) ? _val : _min;
        }
    }
    return _min;
}

Variant MatrixInterface::max() const
{
    auto _max = get(0,0);
    //#pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        int y = (int)idx / size.x;
        int x = idx % size.x;
        const auto _val = get(x,y);
        //#pragma omp critical
        {
            _max = (_val < _max) ? _max : _val;
        }
        
    }
    return _max;
}

void MatrixInterface::normalize(Variant in_min, Variant in_max)
{
    auto _max = max();
    auto _min = min();
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int)idx / size.x;
        const int x = idx % size.x;
        set(x,y, _remap(get(x,y), _min, _max, in_min, in_max));
    }
}

 void MatrixInterface::fill(Vector2i in_size, Array in_data)
{
    set_size(in_size);
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int)idx / size.x;
        const int x = idx % size.x;
        set(x,y,in_size);
    }
}


void MatrixInterface::from_image(const Ref<Image> &in_image, int in_mode)
{
    if (in_image.is_valid())
    {
        set_size(in_image->get_size());
        #pragma omp parallel for num_threads(MAX_OMP)
        for (int idx = 0; idx < size.y * size.x; idx++)
        {
            const int y = (int) idx / size.x;
            const int x = idx % size.x;
            Color col = in_image->get_pixel(x,y);
            switch (in_mode)
            {
                case COLOR :
                    set(x,y,col);
                break;
                case  VECTOR :
                    set(x,y,Vector3(col.r, col.g, col.b));
                break;
                case  BRIGHTNESS :
                    set(x,y,col.get_v());
                break;
                case GRAY :
                    float gray = (col.r + col.g + col.b) / 3.0;
                    set(x,y,gray);
                break;
            }
        }
    }
}

void MatrixInterface::to_image(Ref<Image> out_image) const
{
    //godot::Image::Format format = Image::FORMAT_RF;
    /*
    switch (in_mode)
    {
        case COLOR :
            format = Image::FORMAT_RGBA8;
        break;
        case  VECTOR :
            format = Image::FORMAT_RGB8;
        break;
        default:
        case  BRIGHTNESS :
        case GRAY :
            format = Image::FORMAT_L8;
        break;
    }
    */
    out_image->create( size.x, size.y, false, Image::FORMAT_L8);
    //#pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int) idx / size.x;
        const int x = idx % size.x;
        
        Color col = Color::from_hsv(0.f, 0.f, float(get(x,y)), 1.f);
        out_image->set_pixel(x,y,col);
    }

}


void MatrixInterface::apply_filter(const Ref<MatrixInterface> &in_filter)
{
    // make sure our filter is valid
    if (!in_filter.is_valid())
        return;

    // store filter size
    const auto filter_size = in_filter->get_size();

    // make sure our filter is bigger than 1
    if (filter_size <= Vector2i(1,1))
        return;

    // make sure our filter is odd
    if (filter_size.x % 2 != 1)
        return;
    if (filter_size.y % 2 != 1)
        return;

    // make a temporary vector containing our data
    std::vector<Variant> temp;
    temp.resize(get_size().x * get_size().y);

    // get the offset (distance to center of filter)
    const auto x_offset = filter_size.x - (filter_size.x % 2) / 2;
    const auto y_offset = filter_size.y - (filter_size.y % 2) / 2;

    // for each value of our array 
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int) idx / size.x;
        const int x = idx % size.x;
       
        for (int fidx = 0; fidx < filter_size.y * filter_size.x; fidx++)
        {
            const int fy = (int) idx / size.x;
            const int fx = idx % size.x;

            // find original x corresponding to this
            const int orig_x = fx - x_offset;
            const int orig_y = fy - y_offset;

            Variant A = get(orig_x, orig_y);
            Variant B = in_filter->get(fx, fy);
            Variant C, D;
            bool success = true;
            // multiply, add, and store in temp
            Variant::evaluate(Variant::OP_MULTIPLY, A, B, C, success);

            if (!success) continue;

            Variant::evaluate(Variant::OP_ADD, temp.at(idx), C, D, success);
            if (!success) continue;

            temp.at(idx) = D;
        }
    }

    // apply temp
    #pragma omp parallel for num_threads(MAX_OMP)
    for (int idx = 0; idx < size.y * size.x; idx++)
    {
        const int y = (int) idx / size.x;
        const int x = idx % size.x;
        set(x,y, temp.at(idx));
    }
}