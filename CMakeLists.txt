cmake_minimum_required(VERSION 2.8.4)
project(parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp json.cpp)
add_executable(parser ${SOURCE_FILES})