//
// Created by wands_wang on 2017/11/14.
//

#ifndef CH01_ATTRIBUTEINFO_H
#define CH01_ATTRIBUTEINFO_H

#include <cstdint>

enum ACCESS_FLAG {
    ACC_PUBLIC = 0x0001,
    ACC_PRIVATE = 0x0002,
    ACC_PROTECTED = 0x0004,
    ACC_STATIC = 0x0008,
    ACC_FINAL = 0x0010,
    ACC_VOLATILE = 0x0040,
    ACC_TRANSIENT = 0x0080
};

struct ExceptionInfo {
    /**
     * code代码起始处到异常处理器起始处的偏移量
     * 确定try语句的范围
     */
    uint16_t start_pc;
    uint16_t end_pc;

    /**
     * 当前处理器处理异常的第一条指令，对应catch语句
     */
    uint16_t handle_pc;

    /**
     * 指向常量池中一个class常量的索引
     */
    uint16_t catch_type;
};

struct LineNumberInfo {
    /**
     * 字节码的偏移
     */
    uint16_t start_pc;
    /**
     * 行号
     */
    uint16_t line_number;
};

struct LocalVariableInfo {
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t index;
};

/**
 * 属性可以出现在顶层class文件中，也可以出现在field和method字段中
 */
class AttributeInfo {
public:
    /**
     * 属性名，指向一个常量池utf8的索引
     */
    uint16_t attribute_name_index;
    /**
     * 属性信息的长度
     */
    uint32_t attribute_length;
};

/**
 * SourceFile属性，出现在顶层Class文件中
 */
class SourceFileAttribute : public AttributeInfo {
public:
    uint16_t sourcefile_index;
};

/**
 * 可以描述顶层类，属性和方法，用来表示不是由用户代码产生的
 * attribute_length为0
 */
class SyntheticAttribute : public AttributeInfo {

};

/**
 * 可以出现在ClassFile、method_info和field_info结构中
 * 用于指出类、接口、字段或方法已经不建议使用
 */
class DeprecatedAttribute : public AttributeInfo {

};

/**
 * 描述field_info，每个field_info只能出现一个该属性，并且只有静态字段才会有该属性，
 * 基本类型和String类型才会有该属性，因为他的info是一个索引，指向常量池
 * attribute_length = 2;
 * 虚拟机可以使用ConstantValue为静态变量初始化，也可以使用clinit
 */
class ConstantValueAttribute : public AttributeInfo {
public:
    uint16_t constantvalue_index;
};

/**
 * code是变长属性，只存在于method_info结构中，存放字节码等方法相关信息
 */
class CodeAttribute : public AttributeInfo {
public:
    /**
     * 当前方法被执行引擎执行的时候，在栈帧中需要分配的操作数栈的大小
     */
    uint16_t max_stack;

    /**
     * 局部变量表的大小
     */
    uint16_t max_locals;

    /**
     * 指定该方法的字节码长度,class文件中每条字节码占用一个字节
     */
    uint32_t code_length;
    /**
     * 字节码本身
     */
    uint8_t *code;

    /**
     * 异常表的大小
     */
    uint16_t exception_table_length;
    ExceptionInfo *exception_table;

    /**
     * 当前code属性中，存在的其他属性的个数，可以存在的属性有：LineNumberTable和LocalVariableTable
     */
    uint16_t attributes_count;
    AttributeInfo **attributes;

};

/**
 * 该属性存在于code属性中，它建立了字节码偏移量到源代码行号之间的联系
 */
class LineNumberTableAttribute : public AttributeInfo {
public:
    uint16_t line_number_table_length;
    LineNumberInfo *line_number_table;
};

/**
 * 该属性存在于code属性中，它建立了方法中的局部变量与源代码中局部变量之间的对应关系
 */
class LocalVariableTableAttribute : public AttributeInfo {
public:
    uint16_t local_variable_table_length;
    LocalVariableInfo *local_variable_table;
};

/**
 * 该属性存在与method_info中，描述方法可能抛出的异常，对应于throws后的异常列表
 */
class ExceptionsAttribute : public AttributeInfo {
public:
    /**
     * 该方法要抛出的异常的个数
     */
    uint16_t number_of_exceptions;
    /**
     * 指向常量池中的一个Class常量索引，数组大小为抛出异常的个数
     */
    uint16_t *exception_index_table;
};

#endif //CH01_ATTRIBUTEINFO_H
