#pragma once

#include "stdint.h"

struct PWMInterface {
    virtual bool start() = 0;
    virtual void stop() = 0;
    virtual void updateDuty(const uint32_t duty) = 0;
    virtual uint32_t getDuty() = 0;

    virtual ~PWMInterface() {}
};