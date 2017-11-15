//
// Created by wands_wang on 2017/11/15.
//

#ifndef CH01_LOCAL_VARS_H
#define CH01_LOCAL_VARS_H

#include "slot.h"

class LocalVars {
private:
    Slot *local_vars;
    uint32_t locals_count;

public:
    explicit LocalVars(uint32_t maxLocals);
    void setInt(uint32_t index, int32_t value);
    int32_t getInt(uint32_t index);

    void setFloat(uint32_t index, float value);
    float getFloat(uint32_t index);

    void setLong(uint32_t index, int64_t value);
    int64_t getLong(uint32_t index);

    void setDouble(uint32_t index, double value);
    double getDouble(uint32_t index);

    void setRef(uint32_t index, Object *ref);
    Object *getRef(uint32_t index);
};

#endif //CH01_LOCAL_VARS_H
