/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "map/grid_node.h"
#include "grid/grid_2D.h"

#define GRID_MAX 2048

using namespace Armory;


GridNode::GridNode()
{
    grid.instance();
}

GridNode::~GridNode()
{
    grid.unref();
}

void GridNode::set_grid_size(Point2i new_grid_size)
{
    if(!grid.is_valid())
    {
        grid.instance();
    }

    // avoid zero and negative sizes as well as atrociously big sizes
    grid_size.x = MIN(GRID_MAX,MAX(1, new_grid_size.x));
    grid_size.y = MIN(GRID_MAX,MAX(1, new_grid_size.y));

    // save new grid size
    grid_size = new_grid_size;
    
    // apply
    /// TODO: make this async
    grid.ptr()->resize(grid_size);
}


void GridNode::ready()
{
    set_grid_size(grid_size);
}


void GridNode::_bind_methods() 
{
    // recreation of GDScript/ GDNative functions : 
    ClassDB::bind_method(D_METHOD("ready"), &GridNode::ready);
    ADD_GROUP("Grid", "Grid_");
	BIND_PROPERTY_GETSET(GridNode, Variant::VECTOR2I, grid_size, PROPERTY_HINT_NONE, "Array size");

}
