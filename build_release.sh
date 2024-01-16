#!/bin/bash

mkdir -p build

cd build || exit 1

cmake ..

make

if [ $? -eq 0 ]; then
  echo "Release build succeeded"
else
  echo "Release build failed"
fi
