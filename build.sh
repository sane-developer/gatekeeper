#!/bin/bash

args=("$@")
build_type="Release"
cmake_args=".."

function has_flag() {
  for arg in "${args[@]}"; do
    if [[ "$arg" == "$1" ]]; then
      return 0 
    fi
  done

  return 1
}

if has_flag "-d"; then
  build_type="Debug"
  cmake_args="-DCMAKE_BUILD_TYPE=Debug .."
fi

mkdir -p build || (echo "Could not create build dir." && exit 1)

cd build || (echo "Could not cd into build dir." && exit 1)

cmake $cmake_args || (echo "CMake failed." && exit 1)

make

if [[ $? -eq 0 ]]; then
  echo "$build_type build succeeded."
else
  echo "$build_type build failed."
fi