# Copyright (C)  
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved. 
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# We require CMake >= 3.0
cmake_minimum_required(VERSION 3.0)

# Set projectname (must be done AFTER setting configurationtypes)
project(SunwellCore)

# CMake policies (can not be handled elsewhere)
cmake_policy(SET CMP0005 OLD)
if(POLICY CMP0043)
  cmake_policy(SET CMP0043 OLD) # Disable 'Ignore COMPILE_DEFINITIONS_<Config> properties'
endif()

if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW) # Only interpret if() arguments as variables or keywords when unquoted - prevents intepreting if (SOME_STRING_VARIABLE MATCHES "MSVC") as if (SOME_STRING_VARIABLE MATCHES "1")
endif()

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Set RPATH-handing (CMake parameters)
set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)

# set macro-directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()


include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

# set default buildoptions and print them
include(cmake/options.cmake)

if(WITH_VS_FOLDERS)
    set_property(GLOBAL PROPERTY USE_FOLDERS On)
endif()

# turn off PCH totally if enabled (hidden setting, mainly for devs)
if( NOPCH )
  set(USE_COREPCH 0)
  set(USE_SCRIPTPCH 0)
endif()

include(CheckPlatform)
include(GroupSources)

# Be sure to search only static lib
add_definitions(-DBOOST_ALL_NO_LIB)
if(BOOST_STATIC)
  set(Boost_USE_STATIC_LIBS ON)
endif()
#set(Boost_DEBUG ON)

if(MSVC)
  # Use at least verion 3.8.1 of FindBoost to fix some issues. Especialy in MSVC with fixed Toolset issues.
  # This is a workaround while VisualStudio does not embed higher cmake version than 3.7.2
  if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} LESS 3.8.1)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/macros/FindBoost)
    message(STATUS "FindBoost: included version 3.8.1 of FindBoost is used.")
  endif()
endif()

# Find needed packages and if necessery abort if something important is missing
# example of boost if specific components are required
# ie. find_package(Boost COMPONENTS system filesystem container thread program_options iostreams regex date_time )
find_package(Boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_libraries(${Boost_LIBRARIES})
else()
  message(STATUS "BOOST_ROOT = $ENV{BOOST_ROOT}")
  message(STATUS "BOOST_LIBRARYDIR = $ENV{BOOST_LIBRARYDIR}")
  if ("$ENV{BOOST_ROOT}" STREQUAL "")
    message(WARNING "BOOST_ROOT is not set, please set it correctly to your boost folder.")
  else()
    if ("$ENV{BOOST_LIBRARYDIR}" STREQUAL "")
        message(STATUS "Please put all ${DEP_ARCH} boost lib files in $ENV{BOOST_ROOT}\\lib\\${DEP_ARCH} folder")
        message(STATUS "Or set BOOST_LIBRARYDIR to your boost lib folder.")
    else()
        message(STATUS "BOOST_LIBRARYDIR is set, please verify if correct libs files are in that folder.")
    endif()
  endif()
  message(FATAL_ERROR "This project requires boost.  Please install from http://www.boost.org")
endif()

# basic packagesearching and setup (further support will be needed, this is a preliminary release!)
set(OPENSSL_EXPECTED_VERSION 1.0.0)
set(ACE_EXPECTED_VERSION 5.8.3)

find_package(PCHSupport)
find_package(ACE REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

if( NOT USE_MYSQL_SOURCES )
  find_package(MySQL REQUIRED)
endif()

if( UNIX )
  find_package(Readline)
  find_package(ZLIB)
  find_package(BZip2)
endif()

if(NOT WITHOUT_GIT)
  find_package(Git)
endif()

# Find revision ID and hash of the sourcetree
include(cmake/genrev.cmake)

# print out the results before continuing
include(cmake/showoptions.cmake)

# add dependencies
add_subdirectory(dep)

# add core sources
add_subdirectory(src)
