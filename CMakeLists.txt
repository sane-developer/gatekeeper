#
#  Specifies the required version of CMake.
#

cmake_minimum_required(VERSION 3.20)

#
#  Defines the plugin project metadata.
#

project(gatekeeper LANGUAGES C)

#
#  Defines the C standard.
#

set(CMAKE_C_STANDARD 11)

#
#  Lets the LSP get a hang of the header files.
#

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
