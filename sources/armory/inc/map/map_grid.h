/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MAP_GRID_H
#define MAP_GRID_H

#include "scene/main/node.h" // Node godot class
#include "static_helper.h" // add GETSET_SUPPORT
#include "grid/grid_2D.h"  // grid class
#include "map_core.h"      // map system


/** Armory namespace */
namespace Armory {

// redefine type
using MapGridData = Grid2D<Map::Data>;

/**
 *  MapGrid 
 *  @brief  
 */
class MapGrid : public Node  {
    GDCLASS(MapGrid, Node);

public:

    // ctr
    MapGrid();

    // dstr
    ~MapGrid();


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

#endif //MAP_GRID_H
