cmake_minimum_required(VERSION 2.8.4)
project(lab4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lab4_a ${SOURCE_FILES})
add_executable(lab4_b b.cpp)
add_executable(lab4_c c.cpp)
add_executable(lab4_d d.cpp)
add_executable(lab4_e e.cpp)