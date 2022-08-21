/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef WORLD_CELL_H
#define WORLD_CELL_H


// world
#include "world_inc.h"


namespace armory
{

/**
 * 	@class WorldSolver
 *	Fills a WorldMap with actual data
 */
class WorldSolver :  public Object
{
    GDCLASS(WorldSolver, Object);

private:

    Vector3i Coord;

};
}; // namespace armory

#endif // ! WORLD_CELL_H
