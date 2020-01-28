#pragma once

#include <type_traits>

template< class T >
inline auto enum_value( T value )
{
    return static_cast< typename std::underlying_type<T>::type >( value );
}

#define ENUM_MASK_OPERATORS(T) \
inline T operator ~ (T t) { return (T) (~enum_value(t) ); }                                         \
inline T operator | (T lhs, T rhs) { return (T) (enum_value(lhs) | enum_value(rhs)); }              \
inline T & operator |= (T & lhs, T rhs) { return lhs = (T)(enum_value(lhs) | enum_value(rhs)); }    \
inline T operator & (T lhs, T rhs) { return (T) (enum_value(lhs) & enum_value(rhs)); }              \
inline T & operator &= (T & lhs, T rhs) { return lhs = (T) (enum_value(lhs) & enum_value(rhs));}    \
inline T operator ^ (T lhs, T rhs) { return (T) (enum_value(lhs) ^ enum_value(rhs)); }              \
inline T & operator ^= (T & lhs, T rhs) { return lhs = (T) (enum_value(lhs) ^ enum_value(rhs));}

