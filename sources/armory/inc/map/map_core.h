/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef MAP_CORE_H
#define MAP_CORE_H

/** Armory namespace */
namespace Armory {


namespace Map {
    
    /** 
     * TypeMask
     * @brief Type mask for tiles 
     * 1st bit is Land/Sea 
     * 2nd is modifier,
     *  3 lasts are for height/depth 
     */
    enum class TypeMask : char
    {
        Land_0  = 0b0000000,
        Land_0M = 0b0100000,
        Land_1  = 0b0000001,
        Land_1M = 0b0100001,
        Land_2  = 0b0000010,
        Land_2M = 0b0100010,
        Land_3  = 0b0000011,
        Land_3M = 0b0100011,
        Land_4  = 0b0000100,
        Land_4M = 0b0100100,
        Sea_0   = 0b1000000,
        Sea_0M  = 0b1100000,
        Sea_1   = 0b1000001,
        Sea_1M  = 0b1100001,
        Sea_2   = 0b1000010,
        Sea_2M  = 0b1100010,
        Sea_3   = 0b1000011,
        Sea_3M  = 0b1100011,
        Sea_4   = 0b1000100,
        Sea_4M  = 0b1100100,

    };
    /** 
     * Data
     * @brief contains all info about a tile
     */
    struct Data
    {

        /** type of tile */
        TypeMask type;
    };



} // namespace Map

} // namespace Armory

#endif // MAP_CORE_H