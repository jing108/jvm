cmake_minimum_required(VERSION 3.8)
project(ch01)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp option/cmd.h option/cmd.cpp classpath/classpath.h classpath/entry.h classpath/classpath.cpp classpath/entry.cpp zip/Zip.cpp zip/Zip.h utils/StringUtils.h classfile/ClassFile.h classfile/constantpool.h classfile/ClassFile.cpp utils/NumberUtils.h utils/NumberUtils.cpp classfile/attributeinfo.h rtda/operand_stack.h rtda/object.h rtda/slot.h rtda/local_vars.h rtda/local_vars.cpp rtda/operand_stack.cpp rtda/frame.h rtda/frame.cpp rtda/jvm_stack.h rtda/jvm_stack.cpp)
add_executable(ch01 ${SOURCE_FILES})