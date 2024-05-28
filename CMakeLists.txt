#
#  Global configuration.
#

cmake_minimum_required(VERSION 3.20)

project(gatekeeper LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

#
#  389ds plugin dependencies.
#

find_library(LIB_389DS NAMES 389 PATHS /usr/lib64/dirsrv)

if(NOT LIB_389DS)
    message(FATAL_ERROR "Could not find 389ds library")
endif()

find_library(LIB_SSL NAMES ssl PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_SSL)
    message(FATAL_ERROR "Could not find SSL library")
endif()

find_library(LIB_CRYPTO NAMES crypto PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_CRYPTO)
    message(FATAL_ERROR "Could not find Crypto library")
endif()

find_library(LIB_LDAP NAMES ldap PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_LDAP)
    message(FATAL_ERROR "Could not find LDAP library")
endif()

find_library(LIB_LBER NAMES lber PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_LBER)
    message(FATAL_ERROR "Could not find LBER library")
endif()

find_library(LIB_NSS3 NAMES nss3 PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_NSS3)
    message(FATAL_ERROR "Could not find NSS3 library")
endif()

find_library(LIB_SMIME3 NAMES smime3 PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_SMIME3)
    message(FATAL_ERROR "Could not find SMIME3 library")
endif()

find_library(LIB_NSSUTIL3 NAMES nssutil3 PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_NSSUTIL3)
    message(FATAL_ERROR "Could not find NSSUTIL3 library")
endif()

find_library(LIB_SASL2 NAMES sasl2 PATHS /usr/lib64 /usr/local/lib64)

if(NOT LIB_SASL2)
    message(FATAL_ERROR "Could not find SASL2 library")
endif()

#
#  Builds the SDK.
#

file(GLOB_RECURSE sdk_files
    ./lib/*.c
)

add_library(gatekeeper_sdk SHARED
    ${sdk_files}
)

target_include_directories(gatekeeper_sdk PUBLIC
    ./include/aci_rule/
    ./include/bind_request/
    ./include/plugin_registration/
)

target_link_libraries(gatekeeper_sdk PUBLIC
    ${LIB_389DS}
    ${LIB_SSL}
    ${LIB_CRYPTO}
    ${LIB_LDAP}
    ${LIB_LBER}
    ${LIB_NSS3}
    ${LIB_SMIME3}
    ${LIB_NSSUTIL3}
    ${LIB_SASL2}
)

#
#  Builds the plugin.
#

file(GLOB_RECURSE plugin_files
    ./src/*.c
)

add_library(gatekeeper_plugin SHARED
    ${plugin_files}
)

target_link_libraries(gatekeeper_plugin PRIVATE
    gatekeeper_sdk
)

#
#  Builds the tests.
#

file(GLOB_RECURSE test_files
    ./tests/*.c
)

foreach(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE gatekeeper_sdk)
endforeach()
