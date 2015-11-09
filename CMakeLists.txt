cmake_minimum_required(VERSION 3.0)
project(TimesTables)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -O3")

set(SOURCE_FILES src/main.cpp)
add_executable(TimesTables ${SOURCE_FILES})

target_link_libraries(TimesTables SDL2)