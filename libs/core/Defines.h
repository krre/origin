#pragma once
#include <Origin.h>

#ifdef WIN32
    #define OS_WIN
#endif

#ifdef UNIX
    #define OS_LINUX
#endif

#define DEFINE_ENUM_CLASS_BITWISE_OPERATOR(EnumClass) \
using T = std::underlying_type<EnumClass>::type; \
inline EnumClass operator | (EnumClass lhs, EnumClass rhs) { \
    return (EnumClass)(static_cast<T>(lhs) | static_cast<T>(rhs)); \
} \
\
inline T operator & (EnumClass lhs, EnumClass rhs) { \
    return static_cast<T>(lhs) & static_cast<T>(rhs); \
} \
\
inline EnumClass& operator |= (EnumClass& lhs, EnumClass rhs) { \
    lhs = (EnumClass)(static_cast<T>(lhs) | static_cast<T>(rhs)); \
    return lhs; \
}
