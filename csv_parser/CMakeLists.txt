cmake_minimum_required(VERSION 2.8.4)
project(csv_parser)

file(GLOB SOURCES "csv_parser.cpp")

add_library(csv_parser ${SOURCES})

add_executable(csv_parser_example "example.cpp")
target_link_libraries(csv_parser_example csv_parser)
set_target_properties(csv_parser_example PROPERTIES OUTPUT_NAME csv_parser)
