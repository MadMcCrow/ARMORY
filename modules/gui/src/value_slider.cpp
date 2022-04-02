/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

// header
#include "value_slider.h"

// godot
#include "scene/gui/slider.h"
#include "scene/gui/label.h"


using namespace armory;

ValueSlider::ValueSlider()
{
    set_process(true);
}

void ValueSlider::_bind_methods()
{
    // methods
    ClassDB::bind_method(D_METHOD("get_value"), &ValueSlider::get_value);
    ClassDB::bind_method(D_METHOD("set_display_name", "in_name"), &ValueSlider::set_display_name);
    ClassDB::bind_method(D_METHOD("get_display_name"),            &ValueSlider::get_display_name);
    ClassDB::bind_method(D_METHOD("set_value_map", "in_map"), &ValueSlider::set_value_map);
    ClassDB::bind_method(D_METHOD("get_value_map"),           &ValueSlider::get_value_map);
    ClassDB::bind_method(D_METHOD("set_inner_slider", "in_slider"), &ValueSlider::set_inner_slider);
    ClassDB::bind_method(D_METHOD("get_inner_slider"),              &ValueSlider::get_inner_slider);
    ClassDB::bind_method(D_METHOD("set_name_label", "in_label"), &ValueSlider::set_name_label);
    ClassDB::bind_method(D_METHOD("get_name_label"),             &ValueSlider::get_name_label);
    ClassDB::bind_method(D_METHOD("set_value_label", "in_label"), &ValueSlider::set_value_label);
    ClassDB::bind_method(D_METHOD("get_value_label"),             &ValueSlider::get_value_label);
    ClassDB::bind_method(D_METHOD("set_min_value", "in_min"), &ValueSlider::set_min_value);
    ClassDB::bind_method(D_METHOD("get_min_value"),           &ValueSlider::get_min_value);
    ClassDB::bind_method(D_METHOD("set_max_value", "in_max"), &ValueSlider::set_max_value);
    ClassDB::bind_method(D_METHOD("get_max_value"),           &ValueSlider::get_max_value);

	// Properties
	ADD_GROUP("ARMORY", "armory_");
    ADD_SUBGROUP("GUI", "gui_");
    ADD_SUBGROUP_INDENT("Display","",1);
    ADD_PROPERTY(PropertyInfo(Variant::STRING,  "display_name"), "set_display_name", "get_display_name");
    ADD_SUBGROUP_INDENT("Value","",1);
    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "value_map"), "set_value_map",    "get_value_map");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_value"), "set_min_value", "get_min_value");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_value"), "set_max_value", "get_max_value");
    ADD_SUBGROUP_INDENT("Nodes","", 1);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "inner_slider", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Slider"), "set_inner_slider", "get_inner_slider");
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "name_label",   PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Label"),  "set_name_label",   "get_name_label");
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "value_label",  PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Label"),  "set_value_label",  "get_value_label");
}

void ValueSlider::_notification(int p_notification)
{
    switch (p_notification) 
    {
		case NOTIFICATION_READY:
        {
            if (inner_slider_node())
            {
                inner_slider_node()->connect("value_changed", callable_mp(this, &ValueSlider::value_changed));
            }
        }
        case NOTIFICATION_ENTER_TREE:
		case NOTIFICATION_EXIT_TREE:
		case NOTIFICATION_MOVED_IN_PARENT:
		case NOTIFICATION_PAUSED:
		case NOTIFICATION_UNPAUSED:
		case NOTIFICATION_PARENTED:
		case NOTIFICATION_UNPARENTED:
		case NOTIFICATION_INSTANCED:
		case NOTIFICATION_DRAG_BEGIN:
		case NOTIFICATION_DRAG_END:
		case NOTIFICATION_PATH_RENAMED:
        case NOTIFICATION_PROCESS:
        {
            update_name_label();
            update_value_label();
        } break;
        default:
        break;
    }
}

void ValueSlider::add_child_notify(Node *p_child)
{
    Control::add_child_notify(p_child);
    update_name_label();
    update_value_label();
}

void ValueSlider::remove_child_notify(Node *p_child)
{
    Control::remove_child_notify(p_child);
    update_name_label();
    update_value_label();
}

TypedArray<String> ValueSlider::get_configuration_warnings() const
{
    auto super = Control::get_configuration_warnings();
    if (!inner_slider_node())
        super.push_back(String("Could not find a slider, please set in details"));
    if (!value_label_node())
        super.push_back(String("Could not find a label for value, please set in details"));
    if (!name_label_node())
        super.push_back(String("Could not find a label for name, please set in details"));
    return super;
}

Slider* ValueSlider::inner_slider_node() const
{
    auto node = get_node_or_null(inner_slider);
	return Object::cast_to<Slider>(node);
}

Label* ValueSlider::name_label_node() const
{
    auto node = get_node_or_null(name_label);
	return Object::cast_to<Label>(node);
}

Label* ValueSlider::value_label_node() const
{
    auto node = get_node_or_null(value_label);
	return Object::cast_to<Label>(node);
}

void ValueSlider::update_name_label()
{
    if (const auto label  = name_label_node())
    {
        label->set_text(display_name);
    }
}

void ValueSlider::update_value_label()
{
    const auto slider = inner_slider_node();
    const auto label  = value_label_node();
    if (slider)
    {
        // update slider to behave properly
        // TODO : check it does not change stored value
        slider->set_min(get_min_value());
        slider->set_max(get_max_value());
        // update label based on value
        if (label)
        {
            double value = slider->get_value();
            // find closest in map if map exists:
            if (!value_map.is_empty())
            {
                auto display = value_map.find_closest(value);
                label->set_text(display->value());
                // detent :
                slider->set_value(display->key());
            }
            else
            {
                label->set_text(vformat("%.3f",value));
            }
        }
    }
}


Variant ValueSlider::get_value() const
{
    if (const auto slider = inner_slider_node())
    {
        double value = slider->get_value();
        if (!value_map.is_empty())
        {
            auto display = value_map.find_closest(value);
            return display->value();
        }
        else
        {
           return value;
        }
    }
}

void ValueSlider::set_value(Variant in_value)
{
    // don't know how to implement yet
}

void ValueSlider::set_value_map(const Dictionary& in_map)
{
    value_map.clear();
    int count = in_map.size();
    for (int i = 0; i< count; ++i)
    {
        double key    = in_map.get_key_at_index(i);
        Variant value = in_map.get_value_at_index(i);
        value_map.insert(key, value);
    }
}

Dictionary ValueSlider::get_value_map() const
{
    Dictionary Dict;
    for (auto map_itr : value_map)
    {
        Dict[map_itr.key] = map_itr.value;
    }
    return Dict;
}