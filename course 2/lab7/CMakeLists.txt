cmake_minimum_required(VERSION 3.1)
project(lab7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.cpp)
add_executable(lab7 ${SOURCE_FILES})
add_executable(lab7_d d.cpp)
add_executable(lab7_b b.cpp)
add_executable(lab7_f f.cpp)
add_executable(lab7_e e.cpp)
add_executable(lab7_g g.cpp)