/* Copyright © Noé Perard-Gayot 2020. */
/* Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#ifndef STATIC_HELPER_H
#define STATIC_HELPER_H

#define STRING(s) #s

#define SETTER(var) set_##var
#define GETTER(var) get_##var



/** Generate getter for a property */
#define GET(type, var) inline type GETTER(var)() { return  var ; }
/** Generate setter for a property */
#define SET(type, var) const inline void SETTER(var)(type val) { var = val; }
/** Generate setter and getter for a property */
#define GETSET(type, var)     inline type GETTER(var)() { return  var ; } const inline void SETTER(var)(type val) { var = val; }

/**
 *  Generate the correct ADD_PROPERTY compliant with GETSET
 */
#define ADD_PROPERTY_GETSET(variant, var, property_hint_type, hint) ADD_PROPERTY(PropertyInfo( variant, #var, property_hint_type, hint), STRING(SETTER(var)), STRING(GETTER(var)));

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

}

#endif //STATIC_HELPER_H
