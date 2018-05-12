cmake_minimum_required(VERSION 2.8.4)
project(file_system)

file(GLOB ITEM_SOURCES "file_system_item/*.cpp")

add_library(file_system ${ITEM_SOURCES})
target_link_libraries(file_system stdc++fs)

add_executable(file_system_example "example.cpp")
target_link_libraries(file_system_example file_system)
set_target_properties(file_system_example PROPERTIES OUTPUT_NAME file_system)
