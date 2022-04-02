/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef VALUE_SLIDER_CLASS_H
#define VALUE_SLIDER_CLASS_H

// godot
#include "core/templates/map.h"
#include "core/variant/dictionary.h"
#include "core/string/node_path.h"
#include "scene/gui/control.h"

// we must use this namespace if we want to compile against godot
using namespace godot;


class Slider;
class Label;

// make sure we do not override
namespace armory
{

/**
 * 	@class ValueSlider
 *	a node that have children to behave like a slider, but with numbers 
 *  this class adds detents, and other goodies to it's slider class
 * // TODO: 
 * //       - value types
 * //       - get value
 * //       - change feedback
 * //       - Detents
 * //       - Localisation
 * //       - allow for range instead
 */
class ValueSlider :  public Control
{
    GDCLASS(ValueSlider, Control);

    ValueSlider();

    static void _bind_methods();
    void _notification(int p_notification);

public:

    //<Control overrides>
    virtual void add_child_notify(Node *p_child) override;
	virtual void remove_child_notify(Node *p_child) override;
    virtual TypedArray<String> get_configuration_warnings() const override;
    //<\Control overrides>


private:

    String display_name;

    /** a godot::Slider, can be H or V **/
    NodePath inner_slider;
    Slider* inner_slider_node() const; /** get actual node */

    /** A godot::Label to display the name of the value you're editing (optional) */
    NodePath name_label;
    Label* name_label_node() const; /** get actual node */

    /** A godot::Label to display the value you're editing (optional) */
    NodePath value_label;
    Label* value_label_node() const; /** get actual node */

    /** a map to know what to display on label based on value */
    Map<double, Variant> value_map;

    /** min range */
    double min_value;

    /** max range */
    double max_value;

protected:

    


    /** Update look of label */
    virtual void update_name_label();
    /** Update look of value */
    virtual void update_value_label();

    _FORCE_INLINE_ void value_changed(double in_value) {update_value_label();}


public:

    //<GDScript interface>
    Variant get_value() const;
    void    set_value(Variant in_value);

    /** setter for @see display_name */
    _FORCE_INLINE_ void set_display_name(const String& in_name) {display_name = in_name; update_name_label();}
    /** getter for @see display_name */
    _FORCE_INLINE_ const String& get_display_name() const {return display_name;}

    /** setter for @see value_map */
    void set_value_map(const Dictionary& in_map);
    /** getter for @see value_map */
    Dictionary get_value_map() const;

    /** setter for @see min_value */
    _FORCE_INLINE_ void set_min_value (const double& in_min) {min_value = in_min;}
    /** setter for @see min_value */
    _FORCE_INLINE_ double get_min_value () const {return min_value;}

    /** setter for @see min_value */
    _FORCE_INLINE_ void set_max_value (const double& in_max) {max_value = in_max;}
    /** setter for @see min_value */
    _FORCE_INLINE_ double get_max_value () const {return max_value;}

    /** setter for @see set_inner_slider */
    _FORCE_INLINE_ void set_inner_slider(const NodePath &in_slider) {inner_slider = in_slider; update_value_label();}
    /** getter for @see set_inner_slider */
    _FORCE_INLINE_ const NodePath& get_inner_slider() const {return inner_slider;}

    /** setter for @see name_label */
    _FORCE_INLINE_ void set_name_label(const NodePath& in_label) {name_label = in_label; update_name_label();}
    /** getter for @see name_label */
    _FORCE_INLINE_ const NodePath& get_name_label() const {return name_label;}

    /** setter for @see name_label */
    _FORCE_INLINE_ void set_value_label(const NodePath& in_label) {value_label = in_label; update_value_label();}
    /** getter for @see name_label */
    _FORCE_INLINE_ const NodePath& get_value_label() const {return value_label;}

    //<\GDScript interface>


};

}; // namespace armory


#endif // ! VALUE_SLIDER_CLASS_H
