//
// Created by wands_wang on 2017/11/15.
//

#ifndef CH01_OPERAND_STACK_H
#define CH01_OPERAND_STACK_H

#include <cstdint>
#include "slot.h"

class OperandStack {
private:
    /**
     * 用来记录栈顶位置
     */
    uint32_t size;
    Slot *slots;
    uint32_t maxSize;

public:
    explicit OperandStack(uint32_t maxStack);

    void pushInt(int32_t value);
    int32_t popInt();

    void pushFloat(float value);
    float popFloat();

    void pushLong(int64_t value);
    int64_t popLong();

    void pushDouble(double value);
    double popDouble();

    void pushRef(Object *ref);
    Object *popRef();
};

#endif //CH01_OPERAND_STACK_H
