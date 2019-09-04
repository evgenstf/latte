link_directories(/usr/local/lib)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_custom_target(tests COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)


function(INIT_TEST library_name)
  file(GLOB TEST_FILES "tests/*.cpp")
  add_executable("${library_name}_tests" EXCLUDE_FROM_ALL ${TEST_FILES})
  target_link_libraries("${library_name}_tests" gtest pthread "${library_name}")
  add_dependencies(tests "${library_name}_tests")
  add_test("${library_name}_tests" "./${library_name}_tests")
endfunction()
