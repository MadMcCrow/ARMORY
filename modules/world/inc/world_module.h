/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_MODULE_CLASS_H
#define ARMORY_WORLD_MODULE_CLASS_H

// std
#include <map>
#include <set>

//armory
#include "world_resource.h"
#include "world_statics.h"
#include "world_cell.h"


namespace armory
{

/**
 * 	@class Module
 *	contains the definition of a WFC module
 *  A module has a name (acting as a key), and a pattern.
 *  the pattern is a small subset of tiles
 */
class Module :  public WorldResource
{
    GDCLASS(Module, WorldResource);


    static void _bind_methods();


public:

    Module();

private:

    // simply append a rotation
    struct ModuleCell : public Ref<Cell>
    {
        int rotation : 2;

        ModuleCell() : Ref<Cell>(), rotation(0) {}
        ModuleCell(const Ref<Cell>& in_cell, int in_rotation = 0): Ref<Cell>(in_cell), rotation(in_rotation % 4) {}
    };


    /**
     * cells contained in this module
     */
    std::map<Vector2i,ModuleCell> cells;

    /**
     *  dimension of this module
     *                           some of the cells might be undefined
     */
    Vector2i size;

    /**
     * probability 
     *              this is its intrinsect probability, not relative to the rest
     */
    float probability;

protected:

    /**
     *  setter and getter for modules
     *  we convert to array (of dict), but to avoid casting all the time, we store as std::vector of Struct
     */
    Array get_cells() const;
    void set_cells(const Array& in_modules);

    /**
     *  setter and getter for modules
     *  we convert to array (of dict), but to avoid casting all the time, we store as std::vector of Struct
     */
    float get_probability() const;
    void set_probability(const float& in_probability);

public :

    /** Check if contains a certain cell, used for filtering out modules before testing them for compatibility */
    bool contains_cell(Ref<Cell> cell) const;

    /** calculate size of the module - slow but always exact */ 
    Vector2i calculate_size() const;

    /** get last calculated size */
    const Vector2i& get_size() const {return size;}

    /** get the cells contained in this */
    std::set<Ref<Cell>> get_world_cells() const;

    /** get this module probability */
    _FORCE_INLINE_ const float& get_p() const {return probability;}

    /** get cell, in a const manner */
    _FORCE_INLINE_ const std::map<Vector2i, ModuleCell>& get_cell_map() const {return cells;}

};
        

};



#endif // ! WORLD_MODULE_CLASS_H
