/* Copyright © Noé Perard-Gayot 2021. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef ARMORY_STATIC_HELPER_H
#define ARMORY_STATIC_HELPER_H

#include "core/object/object.h" // for cast

#ifdef TOOLS_ENABLED
#include "core/string/print_string.h"
// print with messabe with extra context
#define LOG(message) print_verbose(String(__PRETTY_FUNCTION__) + String(" : ") + String(message));
#else // TOOLS_ENABLED
// do not print if there's no editor
#define LOG(message) ;
#endif // TOOLS_ENABLED

#define STR(str) #str
#define XSTR(str) STR(str)

#define SETTER(var) set_##var
#define GETTER(var) get_##var

/** Generate getter for a property */
#define GET(type, var) _ALWAYS_INLINE_ type GETTER(var)() const { return  var ; }
/** Generate setter for a property */
#define SET(type, var) _ALWAYS_INLINE_ void SETTER(var)(const type &val) { var = val; }
/** Generate setter and getter for a property */
#define GETSET(type, var)   GET(type, var) SET(type, var)
/** Generate setter for a property , pass by copy */
#define SET_COPY(type, var) _ALWAYS_INLINE_ void SETTER(var)(type val) { var = val; }
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

namespace ARMORY
{
     /**
     * SMALL_NUMBER
     * @brief for whenever you need that "close to zero" feel
     */
    constexpr float SMALL_NUMBER = 0.000001;
    

    
    /**
     * clamp
     * @brief a function to clamp anything implementing '<'
     * @note  similar to std implementation
     */
    template<class T>
    _ALWAYS_INLINE_ constexpr const T& clamp( const T& v, const T& lo, const T& hi )
    {
    	return (v < lo) ? lo : (hi < v) ? hi : v;
    }

    /**
     * smoothstep
     * @brief calculing a somewhat similar to GLSL smoothstep
     * @note  similar to  AMD implementation
     */
    template<class T>
    _ALWAYS_INLINE_ constexpr const T  smoothstep( const T& x, const T& edge0, const T& edge1)
    {
	    // Scale, bias and saturate x to 0..1 range
  	    const auto X = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
  	    // Evaluate polynomial
  	    return X * X * (3 - 2 * X);
    }

    /**
     * lerp
     * @brief a function to linear interpolate anything that implements '*' as multiplication
     * lerp is a + t * (b - a)
     * @param t     your delta, always a float
     * @param a     your previous value
     * @param b     your target
     * @note  similar to std implementation
     */
    template<class T>
    _ALWAYS_INLINE_ constexpr const T lerp( float t, const T& a, const T& b )
    {
    	return a + t * (b - a);
    }

    /** sq @brief  power of two @param a  your value */
    template<class T>
    _ALWAYS_INLINE_ constexpr const T sq(const T& a)   { return a*a;}
    /** p3 @brief  power of three @param a  your value */
    template<class T>
    _ALWAYS_INLINE_ constexpr const T p3(const T& a)   { return a*a*a;}
    /** p4 @brief  power of four @param a  your value */
    template<class T>
    _ALWAYS_INLINE_ constexpr const T p4(const T& a)   { return a*a*a*a;}


    // Dynamically cast an object type-safely.
    template <typename To, typename From>
    _ALWAYS_INLINE_ To* Cast(From* Src)
    {
        return Object::cast_to<To>(Src);

    }
} // namespace ARMORY

#endif //ARMORY_STATIC_HELPER_H