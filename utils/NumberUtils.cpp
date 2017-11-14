//
// Created by wands_wang on 2017/11/13.
//

#include "NumberUtils.h"

uint16_t smallEndian2Big(uint16_t small) {
    return (small << 8) | (small >> 8);
}

uint32_t smallEndian2Big(uint32_t small) {
    uint16_t u1 = small << 16 >> 16;
    uint16_t u2 = small >> 16;
    return (smallEndian2Big(u1) << 16) | smallEndian2Big(u2);
}

uint64_t smallEndian2Big(uint64_t small) {
    uint32_t u1 = small << 32 >> 32;
    uint32_t u2 = small >> 32;
    return (smallEndian2Big(u1) << 32) | smallEndian2Big(u2);
}
