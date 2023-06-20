/// Copyright (c) 2023 Noé Perard-Gayot
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef ARMORY_MACROS_H
#define ARMORY_MACROS_H

/** List of Macros to develop faster */

#define STR(s) #s

/** Theses macros largely simplify creating properties for godot objects */

/** GD property : type, name, default value */
#define GDPROPERTY_DEFAULT(type,name, def) \
    private: \
        type _##name = def; \
    public: \
        inline void set_##name(type value) { _##name = value; } \
        inline const type& get_##name() const { return _##name; }

/** GD property : type, name */
#define GDPROPERTY(type,name) \
    private: \
        type _##name; \
    public: \
        inline void set_##name(type value) { _##name = value; } \
        inline const type& get_##name() const { return _##name; }

/** bind a property declared with GDPROPERTY */
#define BIND_GDPROPERTY(owner, type, name, variant) \
    ClassDB::bind_method(D_METHOD(STR(get_##name)),  &##owner::get_##name); \
    ClassDB::bind_method(D_METHOD(STR(set_##name), #name),  &##owner::set_##name); \
    ADD_PROPERTY(PropertyInfo(variant, STR(_##name)), STR(set_##name), STR(get_##name));


#endif // GDRMS_MACROS_H
