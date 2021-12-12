/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_MODULE_CLASS_H
#define ARMORY_WORLD_MODULE_CLASS_H

// std
#include <map>
#include <set>

// godot
#include "core/object/class_db.h"
#include "core/io/resource.h"

//armory
#include "world_statics.h"
#include "world_cell.h"


namespace armory
{


/**
 *  @class WorldModuleCell
 *  a cell as defined for @see WorldModule
 */
class WorldModuleCell :  public RefCounted
{
    GDCLASS(WorldModuleCell, RefCounted);

public:

    // Cell to use
    Ref<WorldCell> cell;
        
    // North facing rotation [North, South, East, West, None]
    WorldStatics::Direction rotation;

    // this is to make sure rotation shows as enum in the editor
    static void _bind_methods();

    Ref<WorldCell> get_cell() const;
    void set_cell(const Ref<WorldCell>& in_cell);

    int get_rotation() const;
    void set_rotation(const int& in_rotation);
    
};

/**
 * 	@class WorldModule
 *	contains the definition of a WFC module
 *  A module has a name (acting as a key), and a pattern.
 *  the pattern is a small subset of tiles
 */
class WorldModule :  public Resource
{
    GDCLASS(WorldModule, Resource);


    static void _bind_methods();


public:

    WorldModule();

private:



    /**
     * cells contained in this module
     */
    std::map<Vector2i, Ref<WorldModuleCell>> cells;

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
    bool contains_cell(Ref<WorldCell> cell) const;

    /** calculate size of the module - slow but always exact */ 
    Vector2i calculate_size() const;

    /** get last calculated size */
    const Vector2i& get_size() const {return size;}

    /** get the cells contained in this */
    std::set<Ref<WorldCell>> get_world_cells() const;

    /** get this module probability */
    _FORCE_INLINE_ const float& get_p() const {return probability;}


};
        

};



#endif // ! WORLD_MODULE_CLASS_H
