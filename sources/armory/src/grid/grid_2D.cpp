/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "grid/grid_2D.h"
#include "core/math/vector2.h"

#include <math.h>

using namespace Armory;



Point2i    grid_size_to_point_2d (const GridSize2D& gs2d)
{
    return Point2i(gs2d[0U], gs2d[1U]);
}

GridSize2D point_to_grid_size_2d (const Point2i& po2d)
{
    // protecting ourselves from HUGE array
    size_t c[2] = {static_cast<size_t>(abs(po2d.x)), static_cast<size_t>(abs(po2d.y))};
    return GridSize2D(c);
}