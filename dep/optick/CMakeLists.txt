# Copyright (C) 
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SET(optick_STAT_SRCS
    src/optick_core.cpp
    src/optick_gpu.cpp
    src/optick_message.cpp
    src/optick_miniz.cpp
    src/optick_serialization.cpp
    src/optick_server.cpp
)

add_library(optick STATIC ${optick_STAT_SRCS})

target_include_directories( optick 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
)

if(WITH_VS_FOLDERS)
    set_target_properties(optick PROPERTIES FOLDER Dep)
endif()