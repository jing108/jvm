//
// Created by wands_wang on 2017/11/15.
//

#ifndef CH01_JVM_STACK_H
#define CH01_JVM_STACK_H

#include <cstdint>
#include "frame.h"

class Stack {
private:
    uint32_t maxSize;
    uint32_t size;
    Frame *_top;

public:
    explicit Stack(uint32_t maxSize);
    void push(Frame *frame);
    Frame *pop();
    Frame *top();
};

#endif //CH01_JVM_STACK_H
