#pragma once

#include "easy/profiler.h"
#include "Hash/FNV1A.h"

#define PROFILE_SCOPE( name ) EASY_BLOCK( name, Fnv( name ) )
#define PROFILE_FUNCTION(...) EASY_FUNCTION( __VA_ARGS__ )
