//
// Created by wands_wang on 2017/11/13.
//

#ifndef CH01_CLASSFILE_H
#define CH01_CLASSFILE_H

#include <cstdint>
#include <cstring>
#include <fstream>
#include "constantpool.h"
#include "attributeinfo.h"
#include <iostream>

struct FieldInfo {
    /**
     * 访问标志信息：
     * ACC_PUBLIC       0x0001  字段设置为public     类和接口
     * ACC_PRIVATE      0x0002  字段被设为private    类
     * ACC_PROTECTED    0x0004  字段被设为protected  类
     * ACC_STATIC       0x0008  字段被设为static     类和接口
     * ACC_FINAL        0x0010  字段被设为final      类和接口
     * ACC_VOLATILE     0x0040  字段被设为volatile   类
     * ACC_TRANSIENT    0X0080  字段被设为transient  类
     */
    uint16_t access_flags;

    /**
     * 指向常量池utf8常量的索引
     */
    uint16_t name_index;

    /**
     * 指向常量池utf8常量的一个索引
     */
    uint16_t descriptor_index;

    /**
     * 字段的属性表大小
     */
    uint16_t attributes_count;
    AttributeInfo **attributes;
};

struct ClassFile {
    /**
     * class文件magic，0xCAFEBABE
     * 如果不匹配，抛出异常 java.lang.ClassFormatError
     */
    uint32_t magic;

    /**
     * 版本号，虚拟机通过版本号来判断是否支持该Class文件
     * 如果不支持，抛出 java.lang.UnsupportedClassVersionError 异常
     */
    uint16_t minor_version;
    uint16_t major_version;

    /**
     * 常量池信息，索引从1开始，long和double类型常量占用两个常量索引值
     */
    uint16_t constant_pool_count;
    ConstantPool **constant_pool;

    /**
     * 访问标志信息，描述的是当前类或接口的访问修饰符
     *
     */
    uint16_t access_flags;

    /**
     * 类的二进制名，指向一个常量池Class常量的索引
     */
    uint16_t this_class;

    /**
     * 父类的二进制名，指向一个常量池Class常量的索引,java/lang/Object类的该字段索引为0
     */
    uint16_t super_class;

    /**
     * 当前类实现的接口数量，或当前接口继承的超接口的数量
     * 只有当前类直接实现的接口才会被统计
     *
     * 接口其实是常量池中Class常量的索引
     */
    uint16_t interfaces_count;
    uint16_t *interfaces;


    uint16_t fields_count;
    FieldInfo *fields;
    uint16_t methods_count;
    FieldInfo *methods;
    uint16_t attributes_count;
    AttributeInfo **attributes;
};


class ClassReader {
private:
    ClassFile mClassFile;

    ClassReader() {
        memset(&mClassFile, 0x0, sizeof(mClassFile));
    }

public:
    uint16_t minorVersion();

    uint16_t majorVersion();

    ConstantPool *constantPool();

    uint16_t accessFlags();

    static ClassFile *readClass();
};

#endif //CH01_CLASSFILE_H
