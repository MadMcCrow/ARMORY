/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow), François Zajéga (frankiezafe) & Michal Seta (djiamnot)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef GDOSC_REGISTER_TYPES_H
#define GDOSC_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_gdosc_module(ModuleInitializationLevel p_level);
void uninitialize_gdosc_module(ModuleInitializationLevel p_level);

#endif // GDOSC_REGISTER_TYPES_H
