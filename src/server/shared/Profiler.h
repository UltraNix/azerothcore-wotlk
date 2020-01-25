#pragma once

#include "optick.h"
#include "optick_server.h"

#define PROFILE_SCOPE( ... ) OPTICK_EVENT( __VA_ARGS__ )
#define PROFILE_THREAD( ... ) OPTICK_THREAD( __VA_ARGS__ )
#define PROFILE_FRAME( ... ) OPTICK_FRAME( __VA_ARGS__ )

