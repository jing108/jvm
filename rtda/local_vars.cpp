//
// Created by wands_wang on 2017/11/15.
//

#include <cstring>
#include "local_vars.h"

LocalVars::LocalVars(uint32_t maxLocals) {
    if (maxLocals > 0) {
        locals_count = maxLocals;
        local_vars = new Slot[locals_count];
    } else {
        local_vars = nullptr;
        locals_count = 0;
    }
}

void LocalVars::setInt(uint32_t index, int32_t value) {
    uint32_t ui32;
    memcpy(&ui32, &value, 4);
    local_vars[index].num = ui32;
}

int32_t LocalVars::getInt(uint32_t index) {
    return local_vars[index].num;
}

void LocalVars::setFloat(uint32_t index, float value) {
    memcpy(&local_vars[index].num, &value, 4);
}

float LocalVars::getFloat(uint32_t index) {
    float f;
    memcpy(&f, &local_vars[index].num, 4);
    return f;
}

void LocalVars::setLong(uint32_t index, int64_t value) {
    auto *tmp = reinterpret_cast<uint8_t *>(&value);
    memcpy(&local_vars[index].num, tmp, 4);
    memcpy(&local_vars[index + 1].num, tmp + 4, 4);
}

int64_t LocalVars::getLong(uint32_t index) {
    int64_t ui64;
    auto *tmp = reinterpret_cast<uint8_t *>(&ui64);
    memcpy(tmp, &local_vars[index].num, 4);
    memcpy(tmp + 4, &local_vars[index + 1].num, 4);

    return ui64;
}

void LocalVars::setDouble(uint32_t index, double value) {
    auto *tmp = reinterpret_cast<uint8_t *>(&value);
    memcpy(&local_vars[index].num, tmp, 4);
    memcpy(&local_vars[index + 1].num, tmp + 4, 4);
}

double LocalVars::getDouble(uint32_t index) {
    double d;
    auto *tmp = reinterpret_cast<uint8_t *>(&d);
    memcpy(tmp, &local_vars[index].num, 4);
    memcpy(tmp + 4, &local_vars[index + 1].num, 4);

    return d;
}

void LocalVars::setRef(uint32_t index, Object *ref) {
    local_vars[index].ref = ref;
}

Object *LocalVars::getRef(uint32_t index) {
    return local_vars[index].ref;
}
