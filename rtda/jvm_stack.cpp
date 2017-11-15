//
// Created by wands_wang on 2017/11/15.
//

#include <cstdint>
#include <iostream>
#include "jvm_stack.h"

Stack::Stack(uint32_t maxSize) : maxSize(maxSize) {

}

void Stack::push(Frame *frame) {
    if (size > maxSize) {
        std::cout << "java.lang.StackOverflowError" << std::endl;
        return;
    }

    if (_top != nullptr) {
        frame->lower = _top;
    }
    _top = frame;
    size++;
}

Frame *Stack::pop() {
    if (_top == nullptr) {
        std::cout << "jvm stack is empty!" << std::endl;
        exit(-1);
    }

    auto *top = _top;
    _top = top->lower;
    top->lower = nullptr;
    size--;
    return top;
}

Frame *Stack::top() {
    if (_top == nullptr) {
        std::cout << "jvm stack is empty!" << std::endl;
        exit(-1);
    }

    return _top;
}
