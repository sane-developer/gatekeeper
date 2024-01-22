#!/bin/bash

BUILD_TYPE=""

mkdir -p build

cd build || exit 1

if [ "$1" = "--debug" ] ; then
  BUILD_TYPE="Debug"
  cmake -DCMAKE_BUILD_TYPE=Debug ..
else
  BUILD_TYPE="Release"
  cmake ..
fi

make

if [ $? -eq 0 ]; then
  echo "$BUILD_TYPE build succeeded"
else
  echo "$BUILD_TYPE build failed"
fi
