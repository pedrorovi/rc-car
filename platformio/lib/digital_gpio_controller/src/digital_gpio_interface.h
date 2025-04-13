#pragma once

#include "stdint.h"

enum class Port : uint8_t { A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7 };
struct PinPort {
    Port p;
    uint16_t pin;
};

struct DigitalGpioInterface {
    virtual ~DigitalGpioInterface() = default;

    virtual void setup() = 0;
    virtual void digitalWrite(int value) = 0;
    virtual int digitalRead() = 0;
    virtual void toggle() = 0;
};