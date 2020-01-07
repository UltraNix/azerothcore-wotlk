#!/bin/bash

rm -rf build dist
mkdir -p build
mkdir -p dist

cd build

SW_CMAKE_OPTS="${SW_CMAKE_OPTIONS}"
BUILD_OPTS="${SW_BUILD_OPTIONS}"

echo "SW_CMAKE_OPTS = ${SW_CMAKE_OPTS}"
echo "BUILD_OPTS = ${BUILD_OPTS}"

if [[ -z "$SW_CMAKE_OPTS" ]]; then
    echo 'SW_CMAKE_OPTS are empty ! setting default'
    SW_CMAKE_OPTS="-DCMAKE_BUILD_TYPE=RelWithDebInfo"
fi

if [[ -z "$BUILD_OPTS" ]]; then
    echo '$BUILD_OPTS are empty ! setting default'
    BUILD_OPTS="-j`nproc`"
fi

echo "Building with SW_CMAKE_OPTS = ${SW_CMAKE_OPTS}"
echo "Building with BUILD_OPTS = ${BUILD_OPTS}"

echo ""
echo ""
echo "Running command: cmake ..  ${SW_CMAKE_OPTS} -DCMAKE_INSTALL_PREFIX=../dist"
cmake ..  ${SW_CMAKE_OPTS} -DCMAKE_INSTALL_PREFIX="../dist"

echo ""
echo ""
echo "Running command: make ${BUILD_OPTS} install"
make ${BUILD_OPTS} install
