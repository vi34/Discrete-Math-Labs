cmake_minimum_required(VERSION 3.2)
project(lab9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES d.cpp)
add_executable(lab9 ${SOURCE_FILES})
add_executable(lab9_a a.cpp)
add_executable(lab9_e e.cpp)