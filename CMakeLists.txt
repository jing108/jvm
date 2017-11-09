cmake_minimum_required(VERSION 3.8)
project(ch01)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp option/cmd.h option/cmd.cpp)
add_executable(ch01 ${SOURCE_FILES})