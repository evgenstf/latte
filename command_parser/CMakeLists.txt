cmake_minimum_required(VERSION 2.8.4)
project(command_parser)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "command_parser.cpp")

add_library(command_parser ${SOURCES})

add_executable(command_parser_example "example.cpp")
target_link_libraries(command_parser_example command_parser)
set_target_properties(command_parser_example PROPERTIES OUTPUT_NAME command_parser)

include(../cmake/gtest.cmake)
INIT_TEST(command_parser)
