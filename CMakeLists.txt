cmake_minimum_required(VERSION 3.8)
project(ch01)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp option/cmd.h option/cmd.cpp classpath/classpath.h classpath/entry.h classpath/classpath.cpp classpath/entry.cpp zip/Zip.cpp zip/Zip.h utils/StringUtils.h)
add_executable(ch01 ${SOURCE_FILES})