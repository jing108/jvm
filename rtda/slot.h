//
// Created by wands_wang on 2017/11/15.
//

#ifndef CH01_SLOT_H
#define CH01_SLOT_H

#include <cstdint>
#include "object.h"

union Slot {
    uint32_t num;
    Object *ref;
};

#endif //CH01_SLOT_H
