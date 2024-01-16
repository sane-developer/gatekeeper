#!/bin/bash

mkdir -p build

cd build || exit 1

cmake -DCMAKE_BUILD_TYPE=Debug ..

make

if [ $? -eq 0 ]; then
  echo "Debug build succeeded"
else
  echo "Debug build failed"
fi
