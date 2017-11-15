//
// Created by wands_wang on 2017/11/15.
//

#include <cstring>
#include "operand_stack.h"

OperandStack::OperandStack(uint32_t maxStack) {
    if (maxStack > 0) {
        maxSize = maxStack;
        slots = new Slot[maxStack];
        size = 0;
    } else {
        maxStack = 0;
        size = 0;
        slots = nullptr;
    }
}

void OperandStack::pushInt(int32_t value) {
    auto *ui32 = (uint8_t *) &value;
    memcpy(&slots[size++].num, ui32, 4);
}

int32_t OperandStack::popInt() {
    return slots[--size].num;
}

void OperandStack::pushFloat(float value) {
    memcpy(&slots[size++].num, &value, 4);
}

float OperandStack::popFloat() {
    float f;
    memcpy(&f, &slots[--size].num, 4);
    return f;
}

void OperandStack::pushLong(int64_t value) {
    auto *ui64 = (uint8_t *) &value;
    memcpy(&slots[size].num, ui64, 4);
    memcpy(&slots[size + 1].num, ui64 + 4, 4);
    size += 2;
}

int64_t OperandStack::popLong() {
    size -= 2;
    uint64_t value;
    auto *ui64 = (uint8_t *) &value;
    memcpy(ui64, &slots[size].num, 4);
    memcpy(ui64 + 4, &slots[size + 1].num, 4);

    return value;
}

void OperandStack::pushDouble(double value) {
    uint64_t ui64;
    memcpy(&ui64, &value, 8);
    pushLong(ui64);
}

double OperandStack::popDouble() {
    uint64_t ui64 = popLong();
    double value;
    memcpy(&value, &ui64, 8);
    return value;
}

void OperandStack::pushRef(Object *ref) {
    slots[size++].ref = ref;
}

Object *OperandStack::popRef() {
    size--;
    auto *ref = slots[size].ref;
    slots[size].ref = nullptr;
    return ref;
}
