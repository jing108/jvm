//
// Created by wands_wang on 2017/11/15.
//

#ifndef CH01_FRAME_H
#define CH01_FRAME_H

#include "local_vars.h"
#include "operand_stack.h"

class Frame {
public:
    LocalVars localVars;
    OperandStack *operandStack;
    Frame *lower;

    Frame(uint32_t maxLocals, uint32_t maxStack);
};

#endif //CH01_FRAME_H
