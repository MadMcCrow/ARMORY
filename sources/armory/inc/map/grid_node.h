/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_GRID_NODE_H
#define ARMORY_GRID_NODE_H

#include "scene/main/node.h" // Node godot class
#include "static_helper.h" // add GETSET_SUPPORT
#include "grid/grid_2D.h"  // grid class
#include "map_core.h"      // map system


/** Armory namespace */
namespace Armory {

// redefine type
using MapGridData = Grid2D<MapData>;

/**
 *  GridNode 
 *  @brief  
 */
class GridNode : public Node  {
    GDCLASS(GridNode, Node);

public:

    // ctr
    GridNode();

    // dstr
    ~GridNode();


    /**
     *  ready
     *  @brief called when node is ready to start doing stuff
     *  @note  is connected via signal
     */
    virtual void ready();
    

     /**
     *  _bind_methods native function : expose function to GDScript
     *  @note add the function to the reflexion API
     */
    static void _bind_methods();

    /**
     *  grid_size 
     *  @brief How many items in the grid
     * 
     */
    Point2i grid_size;
    GET(Point2i, grid_size)
    void set_grid_size(Point2i new_grid_size);
    
private:
    /**
     *  Grid
     *  @brief actual grid info
     * 
     */
    Ref<MapGridData> grid;

};

} // namespace Armory

#endif //ARMORY_GRID_NODE_H
