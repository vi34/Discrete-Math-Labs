cmake_minimum_required(VERSION 2.8.4)
project(lab5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES a.cpp)
add_executable(lab5 ${SOURCE_FILES})
add_executable(lab5_b b.cpp)