//
// Created by wands_wang on 2017/11/15.
//

#include <cstdint>
#include "frame.h"

Frame::Frame(uint32_t maxLocals, uint32_t maxStack)
        : lower(nullptr),
          operandStack(new OperandStack(maxStack)),
          localVars(maxLocals) {

}
