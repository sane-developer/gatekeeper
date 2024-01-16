#!/bin/bash

mkdir -p build

cd build || exit 1

if [ "$1" = "--debug" ] ; then
  cmake -DCMAKE_BUILD_TYPE=Debug ..
else
  cmake ..
fi

make

if [ $? -eq 0 ]; then
  echo "Debug build succeeded"
else
  echo "Debug build failed"
fi
