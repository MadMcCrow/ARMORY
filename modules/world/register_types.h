/* Copyright © Noé Perard-Gayot 2022. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_WORLD_REGISTER_TYPES_H
#define ARMORY_WORLD_REGISTER_TYPES_H

#include "modules/register_module_types.h"

void initialize_world_module(ModuleInitializationLevel p_level);
void uninitialize_world_module(ModuleInitializationLevel p_level);

#endif // ARMORY_WORLD_REGISTER_TYPES_H
