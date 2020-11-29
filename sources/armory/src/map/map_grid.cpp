/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/map_grid.h"
#include "grid/grid_2D.h"

using namespace Armory;


MapGrid::MapGrid()
{

}

MapGrid::~MapGrid()
{
    if(grid)
        delete grid;
}

void MapGrid::set_grid_size(const Point2i& new_grid_size)
{
    GridSize<2> new_size = point_to_grid_size_2d(new_grid_size);
    if(!grid)
    {
        grid = new MapGridData(new_size);

    }
    else
    {
        grid->resize(new_size);
    }
}

void MapGrid::ready()
{
    
}

void MapGrid::_bind_methods() 
{
    // recreation of GDScript/ GDNative functions 
    ClassDB::bind_method(D_METHOD("ready"), &MapGrid::ready);

}
