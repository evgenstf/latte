cmake_minimum_required(VERSION 2.8.4)
project(latte_library)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(command_parser command_parser)
add_subdirectory(csv_parser csv_parser) 
add_subdirectory(logger logger) 
