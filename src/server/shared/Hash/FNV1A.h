#pragma once

#include <string>

constexpr unsigned int DEFAULT_FNV1A_SEED = 2166136261u;
constexpr unsigned int DEFAULT_FNV1A_PRIME = 16777619u;

template <unsigned int N, unsigned int I>
struct Fnv1a
{
    static unsigned int GetHash( const char( &str )[ N ] )
    {
        return ( Fnv1a<N, I - 1>::GetHash( str ) ^ str[ I - 1 ] ) * DEFAULT_FNV1A_PRIME;
    }
};

template <unsigned int N>
struct Fnv1a<N, 1>
{
    static unsigned int GetHash( const char( &str )[ N ] )
    {
        return ( DEFAULT_FNV1A_SEED ^ str[ 0 ] ) * DEFAULT_FNV1A_PRIME;
    }
};

template <unsigned int N>
static constexpr unsigned int Fnv( const char( &str )[ N ] )
{
    return Fnv1a<N, N>::GetHash( str );
}

static constexpr unsigned int Fnv( const char * data, size_t size, unsigned int hash )
{
    for ( size_t i = 0; i < size; ++i )
    {
        hash ^= *data++;
        hash *= DEFAULT_FNV1A_PRIME;
    }

    return hash;
}

static constexpr unsigned int Fnv( const char * data, unsigned int hash = DEFAULT_FNV1A_SEED )
{
    for ( size_t i = 0; data[ i ]; ++i )
    {
        hash ^= data[ i ];
        hash *= DEFAULT_FNV1A_PRIME;
    }
    return hash;
}

//inline static constexpr unsigned int Fnv( const std::string & data, unsigned int hash = DEFAULT_FNV1A_SEED )
//{
//    return Fnv( data.c_str(), data.size(), hash );
//}
