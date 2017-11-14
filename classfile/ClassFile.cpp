//
// Created by wands_wang on 2017/11/13.
//

#include "ClassFile.h"
#include "../utils/NumberUtils.h"


bool checkVersion(uint16_t major, uint16_t minor) {
    switch (major) {
        case 45:
            return true;

        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
            return minor == 0;

        default:
            return false;
    }

}

void printConstant(ConstantPool **pool, uint16_t constPoolCount) {
    for (int i = 1; i < constPoolCount; i++) {
        uint8_t tag = pool[i]->tag;

        switch (tag) {
            case UTF8: {
                auto *uft8 = (ConstantUtf8Info *) pool[i];
                std::cout << "#" << i << " = utf8           " << uft8->text << std::endl;
                break;
            }

            case INTEGER: {
                auto *integer = (ConstantIntegerInfo *) pool[i];
                std::cout << "#" << i << " = integer        " << integer->value << std::endl;
                break;
            }

            case FLOAT: {
                auto *cfloat = (ConstantFloatInfo *) pool[i];
                std::cout << "#" << i << " = float          " << cfloat->value << std::endl;
                break;
            }
            case LONG: {
                auto *clong = (ConstantLongInfo *) pool[i];
                std::cout << "#" << i << " = long           " << clong->value << std::endl;
                i++;
                break;
            }
            case DOUBLE: {
                auto *cdouble = (ConstantDoubleInfo *) pool[i];
                std::cout << "#" << i << " = double         " << cdouble->value << std::endl;
                i++;
                break;
            }
            case CLASS: {
                auto *cclass = (ConstantClassInfo *) pool[i];
                std::cout << "#" << i << " = class          " << "#" << cclass->name_index << std::endl;
                break;
            }
            case STRING: {
                auto *cstring = (ConstantStringInfo *) pool[i];
                std::cout << "#" << i << " = string         " << "#" << cstring->string_index << std::endl;
                break;
            }
            case FIELD_REF: {
                auto *fieldRef = (ConstantFieldRefInfo *) pool[i];
                std::cout << "#" << i << " = field_ref      " << "#" << fieldRef->class_index << "  #"
                          << fieldRef->name_and_type_index << std::endl;
                break;
            }
            case METHOD_REF: {
                auto *methodRef = (ConstantMethodRefInfo *) pool[i];
                std::cout << "#" << i << " = method_ref     " << "#" << methodRef->class_index << "  #"
                          << methodRef->name_and_type_index << std::endl;
                break;
            }
            case INTERFACE_METHOD_REF: {
                auto *intMethodRef = (ConstantInterfaceMethodRefInfo *) pool[i];
                std::cout << "#" << i << " = interface_method_ref     " << "#" << intMethodRef->class_index << "  #"
                          << intMethodRef->name_and_type_index << std::endl;
                break;
            }
            case NAME_AND_TYPE: {
                auto *nt = (ConstantNameAndTypeInfo *) pool[i];
                std::cout << "#" << i << " = name_and_type  " << "#" << nt->name_index << "  #" << nt->descriptor_index
                          << std::endl;
                break;
            }
        }
    }
}

void *parseAcc(uint16_t acc_flags, std::string &acc) {
    if ((acc_flags & ACC_PUBLIC) == ACC_PUBLIC) {
        acc.append(const_cast<char *>("public "));
    }

    if ((acc_flags & ACC_PRIVATE) == ACC_PRIVATE) {
        acc.append(const_cast<char *>("private "));
    }

    if ((acc_flags & ACC_PROTECTED) == ACC_PROTECTED) {
        acc.append(const_cast<char *>("protected "));
    }

    if ((acc_flags & ACC_STATIC) == ACC_STATIC) {
        acc.append(const_cast<char *>("static "));
    }

    if ((acc_flags & ACC_FINAL) == ACC_FINAL) {
        acc.append(const_cast<char *>("final "));
    }

    if ((acc_flags & ACC_VOLATILE) == ACC_VOLATILE) {
        acc.append(const_cast<char *>("volatile "));
    }

    if ((acc_flags & ACC_TRANSIENT) == ACC_TRANSIENT) {
        acc.append(const_cast<char *>("transient "));
    }
}

void printFieldInfo(FieldInfo *fields, uint16_t fields_count, ConstantPool **pool) {
    for (int i = 0; i < fields_count; i++) {
        FieldInfo field = fields[i];
        std::string acc;
        parseAcc(field.access_flags, acc);
        std::cout << acc;

        auto *utf8Constant = (ConstantUtf8Info *) pool[field.descriptor_index];
        //输出权限标志
        std::cout << utf8Constant->text << " ";

        utf8Constant = (ConstantUtf8Info *) pool[field.name_index];
        std::cout << utf8Constant->text << ";" << std::endl;
    }
}

ClassFile *ClassReader::readClass() {
    char *name = "/Users/wands/IdeaProjects/Algorithm/src/Test.class";
    ClassFile *cf = nullptr;
    std::ifstream in(name, std::ios::binary);

    if (in.is_open()) {
        cf = new ClassFile;
        //读取magic，并校验
        in.read(reinterpret_cast<char *>(&cf->magic), 4);
        cf->magic = smallEndian2Big(cf->magic);
        if (cf->magic != 0xCAFEBABE) {
            std::cout << "java.lang.ClassFormatError: magic!" << std::endl;
            return nullptr;
        }

        //读取版本号，并校验
        in.read(reinterpret_cast<char *>(&cf->minor_version), 2);
        in.read(reinterpret_cast<char *>(&cf->major_version), 2);
        cf->minor_version = smallEndian2Big(cf->minor_version);
        cf->major_version = smallEndian2Big(cf->major_version);
        if (!checkVersion(cf->major_version, cf->minor_version)) {
            std::cout << "java.lang.UnsupportedClassVersionError!" << std::endl;
        }

        //读取常量池
        in.read(reinterpret_cast<char *>(&cf->constant_pool_count), 2);
        cf->constant_pool_count = smallEndian2Big(cf->constant_pool_count);
        cf->constant_pool = static_cast<ConstantPool **>(malloc(sizeof(ConstantPool *) * cf->constant_pool_count));
        for (int i = 1; i < cf->constant_pool_count; i++) {
            char tag = 0;
            in.read(&tag, 1);
            switch (tag) {
                case UTF8: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantUtf8Info)));
                    auto *utf8 = (ConstantUtf8Info *) cf->constant_pool[i];
                    utf8->tag = UTF8;
                    in.read(reinterpret_cast<char *>(&utf8->length), 2);
                    utf8->length = smallEndian2Big(utf8->length);
                    utf8->text = static_cast<char *>(malloc(utf8->length + 1));
                    memset(utf8->text, '\0', utf8->length + 1);
                    in.read(utf8->text, utf8->length);
                    break;
                }

                case INTEGER: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantIntegerInfo)));
                    auto *integer = (ConstantIntegerInfo *) cf->constant_pool[i];
                    integer->tag = INTEGER;
                    in.read(reinterpret_cast<char *>(&integer->value), 4);
                    integer->value = smallEndian2Big(integer->value);
                    break;
                }

                case FLOAT: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantFloatInfo)));
                    auto *constF = (ConstantFloatInfo *) cf->constant_pool[i];
                    constF->tag = FLOAT;
                    in.read(reinterpret_cast<char *>(&constF->value), 4);
                    //todo:需要转换为小端模式
                    break;
                }

                case LONG: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantLongInfo)));
                    auto *constL = (ConstantLongInfo *) cf->constant_pool[i];
                    constL->tag = LONG;
                    in.read(reinterpret_cast<char *>(&constL->value), 8);
                    constL->value = smallEndian2Big(constL->value);
                    i++;
                    break;
                }

                case DOUBLE: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantDoubleInfo)));
                    auto *constDouble = (ConstantDoubleInfo *) cf->constant_pool[i];
                    constDouble->tag = DOUBLE;
                    in.read(reinterpret_cast<char *>(&constDouble->value), 8);
                    //todo:需要转为小端模式
                    i++;
                    break;
                }

                case CLASS: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantClassInfo)));
                    auto *constClass = (ConstantClassInfo *) cf->constant_pool[i];
                    constClass->tag = CLASS;
                    in.read(reinterpret_cast<char *>(&constClass->name_index), 2);
                    constClass->name_index = smallEndian2Big(constClass->name_index);
                    break;
                }

                case STRING: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantStringInfo)));
                    auto *constStr = (ConstantStringInfo *) cf->constant_pool[i];
                    constStr->tag = STRING;
                    in.read(reinterpret_cast<char *>(&constStr->string_index), 2);
                    constStr->string_index = smallEndian2Big(constStr->string_index);
                    break;
                }

                case FIELD_REF: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantFieldRefInfo)));
                    auto *fieldRef = (ConstantFieldRefInfo *) cf->constant_pool[i];
                    fieldRef->tag = FIELD_REF;
                    in.read(reinterpret_cast<char *>(&fieldRef->class_index), 2);
                    in.read(reinterpret_cast<char *>(&fieldRef->name_and_type_index), 2);
                    fieldRef->class_index = smallEndian2Big(fieldRef->class_index);
                    fieldRef->name_and_type_index = smallEndian2Big(fieldRef->name_and_type_index);
                    break;
                }

                case METHOD_REF: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantMethodRefInfo)));
                    auto *methodRef = (ConstantMethodRefInfo *) cf->constant_pool[i];
                    methodRef->tag = METHOD_REF;
                    in.read(reinterpret_cast<char *>(&methodRef->class_index), 2);
                    in.read(reinterpret_cast<char *>(&methodRef->name_and_type_index), 2);
                    methodRef->class_index = smallEndian2Big(methodRef->class_index);
                    methodRef->name_and_type_index = smallEndian2Big(methodRef->name_and_type_index);
                    break;
                }

                case INTERFACE_METHOD_REF: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantInterfaceMethodRefInfo)));
                    auto *interfaceMethodRef = (ConstantInterfaceMethodRefInfo *) cf->constant_pool[i];
                    interfaceMethodRef->tag = INTERFACE_METHOD_REF;
                    in.read(reinterpret_cast<char *>(&interfaceMethodRef->class_index), 2);
                    in.read(reinterpret_cast<char *>(&interfaceMethodRef->name_and_type_index), 2);
                    interfaceMethodRef->class_index = smallEndian2Big(interfaceMethodRef->class_index);
                    interfaceMethodRef->name_and_type_index = smallEndian2Big(interfaceMethodRef->name_and_type_index);
                    break;
                }

                case NAME_AND_TYPE: {
                    cf->constant_pool[i] = static_cast<ConstantPool *>(malloc(sizeof(ConstantNameAndTypeInfo)));
                    auto *nameAndType = (ConstantNameAndTypeInfo *) cf->constant_pool[i];
                    nameAndType->tag = NAME_AND_TYPE;
                    in.read(reinterpret_cast<char *>(&nameAndType->name_index), 2);
                    in.read(reinterpret_cast<char *>(&nameAndType->descriptor_index), 2);
                    nameAndType->name_index = smallEndian2Big(nameAndType->name_index);
                    nameAndType->descriptor_index = smallEndian2Big(nameAndType->descriptor_index);
                    break;
                }
            }
        }
        printConstant(cf->constant_pool, cf->constant_pool_count);

        //读取访问标志信息
        in.read(reinterpret_cast<char *>(&cf->access_flags), 2);
        cf->access_flags = smallEndian2Big(cf->access_flags);

        //类的二进制名
        in.read(reinterpret_cast<char *>(&cf->this_class), 2);
        cf->this_class = smallEndian2Big(cf->this_class);

        //父类的二进制名
        in.read(reinterpret_cast<char *>(&cf->super_class), 2);
        cf->super_class = smallEndian2Big(cf->super_class);

        //读取接口信息
        in.read(reinterpret_cast<char *>(&cf->interfaces_count), 2);
        cf->interfaces_count = smallEndian2Big(cf->interfaces_count);
        if (cf->interfaces_count > 0) {
            cf->interfaces = static_cast<uint16_t *>(malloc(sizeof(uint16_t) * cf->interfaces_count));
            for (int i = 0; i < cf->interfaces_count; i++) {
                in.read(reinterpret_cast<char *>(&cf->interfaces[i]), 2);
                cf->interfaces[i] = smallEndian2Big(cf->interfaces[i]);
            }
        }

        //读取field_info，即类中的字段信息
        in.read(reinterpret_cast<char *>(&cf->fields_count), 2);
        cf->fields_count = smallEndian2Big(cf->fields_count);
        if (cf->fields_count > 0) {
            cf->fields = static_cast<FieldInfo *>(malloc(sizeof(FieldInfo) * cf->fields_count));
            for (int i = 0; i < cf->fields_count; i++) {
                FieldInfo *field = &cf->fields[i];
                in.read(reinterpret_cast<char *>(field), 8);
                field->access_flags = smallEndian2Big(field->access_flags);
                field->name_index = smallEndian2Big(field->name_index);
                field->descriptor_index = smallEndian2Big(field->descriptor_index);
                field->attributes_count = smallEndian2Big(field->attributes_count);
                //读取字段的属性表
                if (field->attributes_count > 0) {
                    field->attributes = static_cast<AttributeInfo **>(malloc(
                            sizeof(AttributeInfo *) * field->attributes_count));
                    for (int j = 0; j < field->attributes_count; j++) {
                        uint16_t attr_name_index;
                        uint32_t attr_length;
                        in.read(reinterpret_cast<char *>(&attr_name_index), 2);
                        in.read(reinterpret_cast<char *>(&attr_length), 4);
                        attr_name_index = smallEndian2Big(attr_name_index);
                        attr_length = smallEndian2Big(attr_length);

                        if (attr_name_index >= 0 && attr_name_index < cf->constant_pool_count) {
                            auto *utf8Constant = (ConstantUtf8Info *) cf->constant_pool[attr_name_index];
                            if (!strcmp(utf8Constant->text, "ConstantValue")) {
                                field->attributes[j] = new ConstantValueAttribute;
                                auto *cv = (ConstantValueAttribute *) field->attributes[j];
                                cv->attribute_name_index = attr_name_index;
                                cv->attribute_length = attr_length;
                                in.read(reinterpret_cast<char *>(&cv->constantvalue_index), cv->attribute_length);
                                cv->constantvalue_index = smallEndian2Big(cv->constantvalue_index);
                            } else if (!strcmp(utf8Constant->text, "Synthetic")) {
                                field->attributes[j] = new SyntheticAttribute;
                                auto *synthetic = (SyntheticAttribute *) field->attributes[i];
                                synthetic->attribute_name_index = attr_name_index;
                                synthetic->attribute_length = attr_length;
                            } else if (!strcmp(utf8Constant->text, "Deprecated")) {
                                field->attributes[j] = new DeprecatedAttribute;
                                auto *deprecated = field->attributes[j];
                                deprecated->attribute_length = attr_length;
                                deprecated->attribute_name_index = attr_name_index;
                            } else {
                                std::cout << "不支持的field_info属性，属性名为: " << utf8Constant->text << std::endl;
                                return nullptr;
                            }
                        } else {
                            std::cout << "field_info属性的attribute_name_index:" << attr_name_index << " 下标不合法"
                                      << std::endl;
                            return nullptr;
                        }

                    }
                }
            }
        }
        printFieldInfo(cf->fields, cf->fields_count, cf->constant_pool);

        //读取method_info信息
        in.read(reinterpret_cast<char *>(&cf->methods_count), 2);
        cf->methods_count = smallEndian2Big(cf->methods_count);
        if (cf->methods_count > 0) {
            cf->methods = static_cast<FieldInfo *>(malloc(sizeof(FieldInfo) * cf->methods_count));
            for (int i = 0; i < cf->methods_count; i++) {
                FieldInfo *method = &cf->methods[i];
                in.read(reinterpret_cast<char *>(method), 8);
                method->access_flags = smallEndian2Big(method->access_flags);
                method->name_index = smallEndian2Big(method->name_index);
                method->descriptor_index = smallEndian2Big(method->descriptor_index);
                method->attributes_count = smallEndian2Big(method->attributes_count);

                if (method->attributes_count > 0) {
                    method->attributes = static_cast<AttributeInfo **>(malloc(
                            sizeof(AttributeInfo *) * method->attributes_count));
                    for (int j = 0; j < method->attributes_count; j++) {
                        uint16_t attr_name_index;
                        uint32_t attr_length;
                        in.read(reinterpret_cast<char *>(&attr_name_index), 2);
                        in.read(reinterpret_cast<char *>(&attr_length), 4);
                        attr_name_index = smallEndian2Big(attr_name_index);
                        attr_length = smallEndian2Big(attr_length);

                        if (attr_name_index >= 0 && attr_name_index < cf->constant_pool_count) {
                            auto *utf8Constant = (ConstantUtf8Info *) cf->constant_pool[attr_name_index];
                            if (!strcmp("Code", utf8Constant->text)) {
                                method->attributes[j] = new CodeAttribute;
                                auto *code = (CodeAttribute *) method->attributes[j];
                                code->attribute_name_index = attr_name_index;
                                code->attribute_length = attr_length;
                                in.read(reinterpret_cast<char *>(&code->max_stack), 2);
                                in.read(reinterpret_cast<char *>(&code->max_locals), 2);
                                in.read(reinterpret_cast<char *>(&code->code_length), 4);
                                code->max_stack = smallEndian2Big(code->max_stack);
                                code->max_locals = smallEndian2Big(code->max_locals);
                                code->code_length = smallEndian2Big(code->code_length);
                                code->code = static_cast<uint8_t *>(malloc(sizeof(uint8_t) * code->code_length));
                                in.read(reinterpret_cast<char *>(code->code), code->code_length);
                                in.read(reinterpret_cast<char *>(&code->exception_table_length), 2);
                                code->exception_table_length = smallEndian2Big(code->exception_table_length);
                                if (code->exception_table_length > 0) {
                                    code->exception_table = static_cast<ExceptionInfo *>(malloc(
                                            sizeof(ExceptionInfo) * code->exception_table_length));
                                    for (int z = 0; z < code->exception_table_length; z++) {
                                        ExceptionInfo *exception = &code->exception_table[z];
                                        in.read(reinterpret_cast<char *>(exception), sizeof(ExceptionInfo));
                                        exception->start_pc = smallEndian2Big(exception->start_pc);
                                        exception->end_pc = smallEndian2Big(exception->end_pc);
                                        exception->handle_pc = smallEndian2Big(exception->handle_pc);
                                        exception->catch_type = smallEndian2Big(exception->catch_type);
                                    }
                                }
                                in.read(reinterpret_cast<char *>(&code->attributes_count), 2);
                                code->attributes_count = smallEndian2Big(code->attributes_count);
                                if (code->attributes_count > 0) {
                                    code->attributes = static_cast<AttributeInfo **>(malloc(
                                            sizeof(AttributeInfo *) * code->attributes_count));
                                    for (int x = 0; x < code->attributes_count; x++) {
                                        uint16_t name_index;
                                        uint32_t len;
                                        in.read(reinterpret_cast<char *>(&name_index), 2);
                                        in.read(reinterpret_cast<char *>(&len), 4);
                                        name_index = smallEndian2Big(name_index);
                                        len = smallEndian2Big(len);
                                        if (name_index >= 0 && name_index < cf->constant_pool_count) {
                                            auto *utf8Constant = (ConstantUtf8Info *) cf->constant_pool[name_index];
                                            if (!strcmp("LineNumberTable", utf8Constant->text)) {
                                                code->attributes[x] = new LineNumberTableAttribute;
                                                auto *line = (LineNumberTableAttribute *) code->attributes[x];
                                                line->attribute_name_index = name_index;
                                                line->attribute_length = len;
                                                in.read(reinterpret_cast<char *>(&line->line_number_table_length), 2);
                                                line->line_number_table_length = smallEndian2Big(
                                                        line->line_number_table_length);
                                                if (line->line_number_table_length > 0) {
                                                    line->line_number_table = static_cast<LineNumberInfo *>(malloc(
                                                            sizeof(LineNumberInfo) * line->line_number_table_length));
                                                    for (int y = 0; y < line->line_number_table_length; y++) {
                                                        LineNumberInfo *lineNumberInfo = &line->line_number_table[y];
                                                        in.read(reinterpret_cast<char *>(lineNumberInfo), 4);
                                                        lineNumberInfo->start_pc = smallEndian2Big(
                                                                lineNumberInfo->start_pc);
                                                        lineNumberInfo->line_number = smallEndian2Big(
                                                                lineNumberInfo->line_number);
                                                    }
                                                }
                                            } else if (!strcmp("LocalVariableTable", utf8Constant->text)) {
                                                code->attributes[x] = new LocalVariableTableAttribute;
                                                auto *local = (LocalVariableTableAttribute *) code->attributes[x];
                                                local->attribute_name_index = name_index;
                                                local->attribute_length = len;
                                                in.read(reinterpret_cast<char *>(&local->local_variable_table_length),
                                                        2);
                                                local->local_variable_table_length = smallEndian2Big(
                                                        local->local_variable_table_length);
                                                if (local->local_variable_table_length > 0) {
                                                    local->local_variable_table = static_cast<LocalVariableInfo *>(malloc(
                                                            sizeof(LocalVariableInfo) *
                                                            local->local_variable_table_length));
                                                    for (int y = 0; y < local->local_variable_table_length; y++) {
                                                        LocalVariableInfo *localVariableInfo = &local->local_variable_table[y];
                                                        in.read(reinterpret_cast<char *>(localVariableInfo), 10);
                                                        localVariableInfo->start_pc = smallEndian2Big(
                                                                localVariableInfo->start_pc);
                                                        localVariableInfo->length = smallEndian2Big(
                                                                localVariableInfo->length);
                                                        localVariableInfo->name_index = smallEndian2Big(
                                                                localVariableInfo->name_index);
                                                        localVariableInfo->descriptor_index = smallEndian2Big(
                                                                localVariableInfo->descriptor_index);
                                                        localVariableInfo->index = smallEndian2Big(
                                                                localVariableInfo->index);
                                                    }
                                                }
                                            } else {
                                                std::cout << "不支持的method_info的code属性的 " << utf8Constant->text << " 属性"
                                                          << std::endl;
                                                return nullptr;
                                            }
                                        } else {
                                            std::cout << "method_field属性中的code属性中的attribute_name_index: " << name_index
                                                      << " 下标不合法" << std::endl;
                                            return nullptr;
                                        }
                                    }
                                }
                            } else if (!strcmp("Synthetic", utf8Constant->text)) {
                                method->attributes[j] = new SyntheticAttribute;
                                auto *synthetic = (SyntheticAttribute *) method->attributes[j];
                                synthetic->attribute_name_index = attr_name_index;
                                synthetic->attribute_length = attr_length;
                            } else if (!strcmp("Deprecated", utf8Constant->text)) {
                                method->attributes[j] = new DeprecatedAttribute;
                                auto *deprecated = (DeprecatedAttribute *) method->attributes[j];
                                deprecated->attribute_name_index = attr_name_index;
                                deprecated->attribute_length = attr_length;
                            } else if (!strcmp("Exceptions", utf8Constant->text)) {
                                method->attributes[j] = new ExceptionsAttribute;
                                auto *exceptions = (ExceptionsAttribute *) method->attributes[j];
                                exceptions->attribute_name_index = attr_name_index;
                                exceptions->attribute_length = attr_length;
                                in.read(reinterpret_cast<char *>(&exceptions->number_of_exceptions), 2);
                                exceptions->number_of_exceptions = smallEndian2Big(exceptions->number_of_exceptions);
                                if (exceptions->number_of_exceptions > 0) {
                                    exceptions->exception_index_table = static_cast<uint16_t *>(malloc(
                                            sizeof(uint16_t) * exceptions->number_of_exceptions));
                                    for (int x = 0; x < exceptions->number_of_exceptions; x++) {
                                        exceptions->exception_index_table[x] = smallEndian2Big(
                                                exceptions->exception_index_table[x]);
                                    }
                                }
                            } else {
                                std::cout << "不支持的method_field属性: " << utf8Constant->text << std::endl;
                                return nullptr;
                            }
                        } else {
                            std::cout << "method_field属性的attribute_name_index:" << attr_name_index << " 下标不合法"
                                      << std::endl;
                            return nullptr;
                        }
                    }
                }
            }
        }
        printFieldInfo(cf->methods, cf->methods_count, cf->constant_pool);

        //读取属性信息
        in.read(reinterpret_cast<char *>(&cf->attributes_count), 2);
        cf->attributes_count = smallEndian2Big(cf->attributes_count);
        if (cf->attributes_count > 0) {
            cf->attributes = static_cast<AttributeInfo **>(malloc(sizeof(AttributeInfo *) * cf->attributes_count));
            for (int i = 0; i < cf->attributes_count; i++) {
                uint16_t attr_name_index;
                uint32_t attr_length;
                in.read(reinterpret_cast<char *>(&attr_name_index), 2);
                in.read(reinterpret_cast<char *>(&attr_length), 4);
                attr_name_index = smallEndian2Big(attr_name_index);
                attr_length = smallEndian2Big(attr_length);

                if (attr_name_index >= 0 && attr_name_index < cf->constant_pool_count) {
                    auto *utf8Constant = (ConstantUtf8Info *) cf->constant_pool[attr_name_index];
                    if (!strcmp("SourceFile", utf8Constant->text)) {
                        cf->attributes[i] = new SourceFileAttribute;
                        auto *source = (SourceFileAttribute *) cf->attributes[i];
                        source->attribute_name_index = attr_name_index;
                        source->attribute_length = attr_length;
                        in.read(reinterpret_cast<char *>(&source->sourcefile_index), 2);
                        source->sourcefile_index = smallEndian2Big(source->sourcefile_index);
                    } else if (!strcmp("Synthetic", utf8Constant->text)) {
                        cf->attributes[i] = new SyntheticAttribute;
                        auto *synthetic = (SyntheticAttribute *) cf->attributes[i];
                        synthetic->attribute_name_index = attr_name_index;
                        synthetic->attribute_length = attr_length;
                    } else if (!strcmp("Deprecated", utf8Constant->text)) {
                        cf->attributes[i] = new DeprecatedAttribute;
                        auto *deprecated = (DeprecatedAttribute *) cf->attributes[i];
                        deprecated->attribute_name_index = attr_name_index;
                        deprecated->attribute_length = attr_length;
                    } else {
                        std::cout << "不支持的class属性:" << utf8Constant->text << std::endl;
                        return nullptr;
                    }
                } else {
                    std::cout << "class file 属性的attribute_name_index:" << attr_name_index << "  下标不合法" << std::endl;
                    return nullptr;
                }
            }
        }

        return cf;
    }

}
