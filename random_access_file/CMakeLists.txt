cmake_minimum_required(VERSION 2.8.4)
project(random_access_file)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(random_access_file "random_access_file.cpp")

add_executable(random_access_file_bin "example.cpp")
target_link_libraries(random_access_file_bin random_access_file)
set_target_properties(random_access_file_bin PROPERTIES OUTPUT_file random_access_file)
