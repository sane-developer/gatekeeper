### Metadata

cmake_minimum_required(VERSION 3.22)

project(gatekeeper C)

set(CMAKE_C_STANDARD 11)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

### Library

file(GLOB LIB_FILES
    ./src/parsers/*.c
    ./src/types/*.c
    ./src/utilities/*.c
    ./src/validators/*.c
)

add_library(gatekeeper_sdk SHARED ${LIB_FILES})

### Plugin

file(GLOB PLUGIN_FILES
    ./src/plugin.c
)

file(GLOB PLUGIN_DEPENDENCIES
    ./src/allocators/slapd_allocator.c
    ./src/loggers/slapd_logger.c
)

add_library(gatekeeper_plugin SHARED ${PLUGIN_FILES} ${PLUGIN_DEPENDENCIES})
target_link_libraries(gatekeeper_plugin gatekeeper_sdk)

### Tests

file(GLOB PARSERS_TESTS
    ./tests/parsers/*.c
)

file(GLOB STRINGS_TESTS
    ./tests/strings/*.c
)

file(GLOB TEST_DEPENDENCIES
    ./src/allocators/std_allocator.c
    ./src/loggers/std_logger.c
)

foreach(TEST_FILE ${PARSERS_TESTS})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${TEST_DEPENDENCIES})
    target_compile_options(${TEST_NAME} PRIVATE -DDISABLE_LOGGING)
    target_link_libraries(${TEST_NAME} gatekeeper_sdk)
endforeach()

foreach(TEST_FILE ${STRINGS_TESTS})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${TEST_DEPENDENCIES})
    target_link_libraries(${TEST_NAME} gatekeeper_sdk)
endforeach()