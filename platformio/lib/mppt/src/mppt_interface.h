#pragma once

#include <stdint.h>

struct MpptData_t {
    float voltage_v;
    float current_amp;
    float power_watt;

    void operator=(const MpptData_t& other) {
        voltage_v = other.voltage_v;
        current_amp = other.current_amp;
        power_watt = other.power_watt;
    }

    void operator()(const float voltage_v, const float current_amp) {
        this->voltage_v = voltage_v;
        this->current_amp = current_amp;
        this->power_watt = voltage_v * current_amp;
    }
};

struct PwmData_t {
    uint16_t min;
    uint16_t max;
    uint16_t step;
    uint16_t val;

    void operator()(const uint16_t min, const uint16_t max, const uint16_t step) {
        this->min = min;
        this->max = max;
        this->step = step;
        this->val = (max + min) / 2;
    }

    void increase() {
        if (val < max) {
            val += step;
        }
    }

    void decrease() {
        if (val > min) {
            val -= step;
        }
    }
};

class MpptInterface {
   public:
    virtual uint16_t update(const float voltage_v, const float current_amp) = 0;

    virtual ~MpptInterface() {}
};
