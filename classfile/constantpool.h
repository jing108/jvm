//
// Created by wands_wang on 2017/11/13.
//

#ifndef CH01_CONSTANTPOOL_H
#define CH01_CONSTANTPOOL_H

#include <cstdint>

enum ConstantTag {
    UTF8 = 1,
    INTEGER = 3,
    FLOAT = 4,
    LONG = 5,
    DOUBLE = 6,
    CLASS = 7,
    STRING = 8,
    FIELD_REF = 9,
    METHOD_REF = 10,
    INTERFACE_METHOD_REF = 11,
    NAME_AND_TYPE = 12,
    METHOD_HANDLE = 15,
    METHOD_TYPE = 16,
    INVOKE_DYNAMIC = 18
};

class ConstantPool {
public:
    uint8_t tag;
};

class ConstantUtf8Info : public ConstantPool {
public:
    uint16_t length;
    char *text;
};

class ConstantIntegerInfo : public ConstantPool {
public:
    uint32_t value;
};

class ConstantFloatInfo : public ConstantPool {
public:
    //todo: 先这样表示float
    uint32_t value;
};

class ConstantLongInfo : public ConstantPool {
public:
    //todo: 先这样声明long
    uint64_t value;
};

class ConstantDoubleInfo : public ConstantPool {
public:
    //todo:先这样声明double
    uint64_t value;
};

class ConstantClassInfo : public ConstantPool {
public:
    uint16_t name_index;
};

class ConstantStringInfo : public ConstantPool {
public:
    uint16_t string_index;
};

class ConstantFieldRefInfo : public ConstantPool {
public:
    uint16_t class_index;
    uint16_t name_and_type_index;
};

class ConstantMethodRefInfo : public ConstantPool {
public:
    uint16_t class_index;
    uint16_t name_and_type_index;
};

class ConstantInterfaceMethodRefInfo : public ConstantPool {
public:
    uint16_t class_index;
    uint16_t name_and_type_index;
};

class ConstantNameAndTypeInfo :public ConstantPool {
public:
    uint16_t name_index;
    uint16_t descriptor_index;
};

#endif //CH01_CONSTANTPOOL_H
