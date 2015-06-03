cmake_minimum_required(VERSION 2.8.4)
project(lab6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.cpp)
add_executable(lab6 ${SOURCE_FILES})
add_executable(lab6_c c.cpp)
add_executable(lab6_b b.cpp)
add_executable(lab6_d d.cpp)
add_executable(diff diff_eq.cpp)