#pragma once
#include "Refl/refl.hpp"

#define ATTRIBUTE_CLASS_NAME "reflect-class;"
#define ATTRIBUTE_STRUCT_NAME "reflect-struct;"
#define ATTRIBUTE_PROPERTY_NAME "reflect-property;"
#define ATTRIBUTE_FUNCTION_NAME "reflect-function;"

#if METAREFLECT
    #define CLASS(...) __attribute__((annotate(ATTRIBUTE_CLASS_NAME #__VA_ARGS__)))
    #define STRUCT(...) __attribute__((annotate(ATTRIBUTE_STRUCT_NAME #__VA_ARGS__)))
    #define PROPERTY(...)  __attribute__((annotate(ATTRIBUTE_PROPERTY_NAME #__VA_ARGS__)))
    #define FUNCTION(...) __attribute__((annotate(ATTRIBUTE_FUNCTION_NAME #__VA_ARGS__)))
#else /* else METAREFLECT */
    #define CLASS(...)
    #define STRUCT(...)
    #define PROPERTY(...)
    #define FUNCTION(...)
#endif /* METAREFLECT */

#define GENERATED_BODY(...)
#define META_REFLECT(...)

struct Serializable : refl::attr::usage::member
{
};