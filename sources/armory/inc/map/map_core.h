/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_MAP_CORE_H
#define ARMORY_MAP_CORE_H

/** Armory namespace */
namespace Armory {


namespace Map {
    
    /** 
     * Data
     * @brief contains all info about a tile
     */
    struct Data
    {
        /**
         *  sign:  0 is sea, 1 is land 
         */
        unsigned int sign     : 1;

        /**
         *  Absolute Height/Depth, can be 0,1,2,3 
         */
        unsigned int height   : 2;

        /**
         *  Modifier is River  on 0
         *  Modifier is trees  on 1
         *  Modifier is rocks  on 2
         *  Modifier is canyon on 3
         */
        unsigned int modifier : 1;

    };
    
} // namespace Map


} // namespace Armory

#endif // ARMORY_MAP_CORE_H