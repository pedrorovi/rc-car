#pragma once

#include "stepper_interface.h"

#include "pwm_interface.h"

#include <iostream>

class StepperController : public StepperInterface {
   public:
    StepperController(PWMInterface* pwm) : pwm(pwm) {}
    ~StepperController() {}

    bool setup() override;
    void setDirection(const uint32_t direction) override;
    uint32_t getDirection() override;
    void straight() override;

   private:
    PWMInterface* pwm;
};