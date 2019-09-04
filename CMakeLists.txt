cmake_minimum_required(VERSION 2.8.4)
project(latte_library)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(command_parser command_parser)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_custom_target(tests COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable(latte_library_tests EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries(latte_library_tests gtest pthread command_parser)
add_dependencies(tests latte_library_tests)
add_test(latte_library_tests ./latte_library_tests)
