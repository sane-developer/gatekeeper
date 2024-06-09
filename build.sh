#!/bin/bash

#
#  Creates build directory for the plugin.
#

mkdir -p build

#
#  Moves to the build directory of the plugin.
#

cd build

#
#  Builds CMake into Makefile.
#

if [[ "$1" == "-d" ]] ; then
  cmake -DCMAKE_BUILD_TYPE=Debug ..
else
  cmake -DCMAKE_BUILD_TYPE=Release ..
fi

#
#  Compiles the project targets.
#

make
