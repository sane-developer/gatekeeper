#
# Setup projects metadata.
#

cmake_minimum_required(VERSION 3.20)

project(gatekeeper LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/../build/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

#
# Build library out of framework source files.
#

file(GLOB_RECURSE framework_src_files ./framework/aci_rule/*.c
     ./framework/bind_request/*.c ./framework/plugin_lanucher/*.c)

add_library(gatekeeper_framework SHARED ${framework_src_files})

target_include_directories(
  gatekeeper_framework
  PUBLIC ./framework/aci_rule/
         ./framework/aci_rule/expressions/
         ./framework/aci_rule/expressions/dn/
         ./framework/aci_rule/expressions/ip/
         ./framework/aci_rule/expressions/dns/
         ./framework/aci_rule/expressions/roles/
         ./framework/aci_rule/expressions/groups/
         ./framework/aci_rule/expressions/attributes/
         ./framework/aci_rule/expressions/day_of_week/
         ./framework/aci_rule/expressions/time_of_day/
         ./framework/bind_request/
         ./framework/plugin_launcher/)

target_link_libraries(gatekeeper_framework PUBLIC -L/usr/lib64/dirsrv -lnspr4)

#
# Build library out of plugin source files.
#

file(GLOB_RECURSE plugin_src_files ./bootstrap/*.c)

add_library(gatekeeper_plugin SHARED ${plugin_src_files})

target_link_libraries(gatekeeper_plugin PRIVATE gatekeeper_framework)
