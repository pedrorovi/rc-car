#pragma once

#include "stdint.h"

struct PPMInInterface {
    virtual bool start() = 0;
    virtual void stop() = 0;
    virtual float getPulseWidthUs() = 0;
    virtual void updatePulseWidth() = 0;
};