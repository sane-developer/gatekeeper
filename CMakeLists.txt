cmake_minimum_required(VERSION 3.22)

project(gatekeeper C)

set(CMAKE_C_STANDARD 11)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

set(PLUGIN_SRC_FILES)

set(PLUGIN_LIB_SRC_FILES
    ./src/utilities/string_utils.c
    ./src/utilities/string_utils.h
)

set(IS_NUMBER_TESTS_SRC_FILES
    ./tests/utilities/is_number_tests.c
)

set(ERASE_WHITESPACES_TESTS_SRC_FILES
    ./tests/utilities/erase_whitespaces_tests.c
)

set(EXTRACT_KEY_VALUE_PAIR_TESTS_SRC_FILES
    ./tests/utilities/extract_key_value_pair_tests.c
)

add_library(gatekeeper_lib SHARED ${PLUGIN_LIB_SRC_FILES})
#target_compile_options(gatekeeper_lib PRIVATE -DDISABLE_LOGGING)

add_executable(is_number_tests ${IS_NUMBER_TESTS_SRC_FILES})
target_link_libraries(is_number_tests gatekeeper_lib)

add_executable(erase_whitespaces_tests ${ERASE_WHITESPACES_TESTS_SRC_FILES})
target_link_libraries(erase_whitespaces_tests gatekeeper_lib)

add_executable(extract_key_value_tests ${EXTRACT_KEY_VALUE_PAIR_TESTS_SRC_FILES})
target_link_libraries(extract_key_value_tests gatekeeper_lib)