cmake_minimum_required(VERSION 2.8.4)
project(logger)

file(GLOB SOURCES "logger.cpp")

add_library(logger ${SOURCES})
target_link_libraries(logger pthread)

add_executable(logger_example "example.cpp")
target_link_libraries(logger_example logger)
set_target_properties(logger_example PROPERTIES OUTPUT_NAME logger)
