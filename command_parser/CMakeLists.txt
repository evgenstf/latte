cmake_minimum_required(VERSION 2.8.4)
project(command_parser)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "command_parser.cpp")

add_library(command_parser ${SOURCES})

add_executable(command_parser_example "example.cpp")
target_link_libraries(command_parser_example command_parser)
set_target_properties(command_parser_example PROPERTIES OUTPUT_NAME command_parser)

include(../cmake/gtest.cmake)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable(command_parser_tests EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries(command_parser_tests gtest pthread command_parser)
add_dependencies(tests command_parser_tests)
add_test(command_parser_tests ./command_parser_tests)
