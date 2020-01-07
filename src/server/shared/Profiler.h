#pragma once

#include "easy/profiler.h"

#define PROFILE_SCOPE( name ) EASY_BLOCK( name )
#define PROFILE_FUNCTION(...) EASY_FUNCTION( __VA_ARGS__ )
