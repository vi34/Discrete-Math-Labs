cmake_minimum_required(VERSION 3.1)
project(lab8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.cpp)
add_executable(lab8 ${SOURCE_FILES})
add_executable(lab8_b b.cpp)
add_executable(lab8_f f.cpp)
add_executable(lab8_c c.cpp)
add_executable(lab8_e e.cpp)
add_executable(lab8_g g.cpp)