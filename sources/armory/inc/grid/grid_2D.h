/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef GRID_2D_H
#define GRID_2D_H

// Godot Includes
#include "grid_core.h"

namespace Armory
{

/** GridSize2D , 2D variant @see GridSize.  */
using GridSize2D = GridSize<2>;

/** Grid2D , 2D variant @see Grid  */
template <typename T>
using Grid2D = Grid<T, 2>;

// no need to alias private class :)


/** conversion functions */
Point2i    grid_size_to_point_2d (const GridSize2D& gs2d);
GridSize2D point_to_grid_size_2d (const Point2i& po2d);

} // namespace Armory


#endif //GRID_2D_H