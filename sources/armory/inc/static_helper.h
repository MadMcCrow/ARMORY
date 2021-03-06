/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_STATIC_HELPER_H
#define ARMORY_STATIC_HELPER_H

#include "core/object/object.h" // for cast

#define STR(str) #str
#define XSTR(str) STR(str)

#define SETTER(var) set_##var
#define GETTER(var) get_##var

/** Generate getter for a property */
#define GET(type, var) inline type GETTER(var)() const { return  var ; }
/** Generate setter for a property */
#define SET(type, var) inline void SETTER(var)(const type &val) { var = val; }
/** Generate setter and getter for a property */
#define GETSET(type, var)   GET(type, var) SET(type, var)
/** Generate setter for a property , pass by copy */
#define SET_COPY(type, var) inline void SETTER(var)(type val) { var = val; }
/** Generate setter and getter for a property,  pass by copy */
#define GETSET_COPY(type, var)  GET(type, var) SET_COPY(type, var)

/** Bind setter for a property */
#define BIND_SET(var, class) ClassDB::bind_method(D_METHOD( XSTR(SETTER(var)), STR(var)), &class::SETTER(var));
/** Bind Getter for a property */
#define BIND_GET(var, class) ClassDB::bind_method(D_METHOD( XSTR(GETTER(var))), &class::GETTER(var));
/** Generate setter and getter for a property */
#define BIND_GETSET(var, class) BIND_SET(var, class) BIND_GET(var, class)

/**  Generate the correct ADD_PROPERTY compliant with GETSET */
#define ADD_PROPERTY_GETSET(variant, var, property_hint_type, hint) ADD_PROPERTY(PropertyInfo( variant, #var, property_hint_type, hint), XSTR(SETTER(var)), XSTR(GETTER(var)) );

/**  Generate the correct ADD_PROPERTY compliant with GETSET */
#define BIND_PROPERTY_ENUM(class, var, hint)  BIND_GETSET(var, class) ADD_PROPERTY(PropertyInfo( Variant::INT, #var, PROPERTY_HINT_ENUM, hint), XSTR(SETTER(var)), XSTR(GETTER(var)) );


/**  Generate the correct ADD_PROPERTY compliant with GETSET */
#define BIND_PROPERTY_GETSET(class, variant, var, property_hint_type, hint) BIND_GETSET(var, class) ADD_PROPERTY_GETSET(variant, var, property_hint_type, hint);


class Object;
class String;

namespace Armory
{
     /**
     * SMALL_NUMBER
     * @brief for whenever you need that "close to zero" feel
     */
    constexpr float SMALL_NUMBER = 0.000001;
    

     /**
     * print_msg
     * @brief prints debug info with some added context
     */
    void print_msg( Object * obj, const char* txt);
    void print_msg( Object * obj, const String &txt );
    
    /**
     * clamp
     * @brief a function to clamp anything implementing '<'
     * @note shamelessly stolen from std
     */
    template<class T>
    constexpr const T& clamp( const T& v, const T& lo, const T& hi )
    {
    	return (v < lo) ? lo : (hi < v) ? hi : v;
    }

    /**
     * smoothstep
     * @brief calculing a somewhat similar to GLSL smoothstep
     * @note shamelessly stolen from AMD
     */
    template<class T>
    constexpr const T  smoothstep( const T& x, const T& edge0, const T& edge1)
    {
	    // Scale, bias and saturate x to 0..1 range
  	    const auto X = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
  	    // Evaluate polynomial
  	    return X * X * (3 - 2 * X);
    }

    // Dynamically cast an object type-safely.
    template <typename To, typename From>
    inline To* Cast(From* Src)
    {
        return Object::cast_to<To>(Src);

    }

}
#endif //ARMORY_STATIC_HELPER_H
