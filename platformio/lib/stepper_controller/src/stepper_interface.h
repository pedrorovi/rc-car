#pragma once

#include <stdint.h>

class StepperInterface {
   public:
    virtual bool setup() = 0;
    virtual void setDirection(const uint32_t percent) = 0;
    virtual uint32_t getDirection() = 0;
    virtual void straight() = 0;

    virtual ~StepperInterface() {}
};
