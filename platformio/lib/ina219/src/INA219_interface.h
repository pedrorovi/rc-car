#pragma once

#include "stdint.h"

class INA219_interface {
   public:
    virtual void setCalibration_32V_2A(void) = 0;
    virtual void setCalibration_16V_6A(void) = 0;
    virtual void setCalibration_32V_1A(void) = 0;
    virtual void setCalibration_16V_400mA(void) = 0;
    virtual float getBusVoltage_V(void) = 0;
    virtual float getShuntVoltage_mV(void) = 0;
    virtual float getCurrent_mA(void) = 0;
    virtual float getPower_mW(void) = 0;
    virtual bool getCurrentAmps(float* amps) = 0;
};
