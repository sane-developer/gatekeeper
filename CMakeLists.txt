#
#  Specifies the required version of CMake.
#

cmake_minimum_required(VERSION 3.22)

#
#  Defines the plugin project metadata.
#

project(gatekeeper LANGUAGES C)

#
#  Defines the C standard.
#

set(CMAKE_C_STANDARD 11)

#
#  Defines the target directories for libs and executables.
#

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

#
#  Adds remaining CMakeLists.txt to the compilation process.
#

add_subdirectory(sdk)

add_subdirectory(src)