/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */


#include "register_types.h"

// ValueSlider
#include "value_slider.h"


void register_gui_types() 
{
    ClassDB::register_class<armory::ValueSlider>();
}

void unregister_gui_types() 
{
}

