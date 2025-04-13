#pragma once

#include <stdint.h>

class MotorInterface {
   public:
    virtual bool setup() = 0;
    virtual void setSpeed(const int16_t percent) = 0;
    virtual uint32_t getSpeed() = 0;
    virtual void stop() = 0;
    virtual bool enable() = 0;
    virtual bool disable() = 0;

    virtual ~MotorInterface() {}
};
