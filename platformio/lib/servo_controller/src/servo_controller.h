#pragma once

#include "servo_interface.h"

#include "pwm_interface.h"

#include <iostream>

class ServoController : public ServoInterface {
   public:
    ServoController(PWMInterface* pwm) : pwm(pwm) {}
    ~ServoController() {}

    bool setup() override;
    void setDirection(const uint32_t direction) override;
    uint32_t getDirection() override;
    void straight() override;

   private:
    PWMInterface* pwm;
};