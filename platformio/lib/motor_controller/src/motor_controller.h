#pragma once

#include "motor_interface.h"

#include "digital_gpio_interface.h"
#include "pid.h"
#include "pwm_interface.h"

#include <iostream>

class MotorController : public MotorInterface {
   public:
    MotorController(PWMInterface* pwm, DigitalGpioInterface* enable, PID* pid) : pwm(pwm), _enable(enable), pid(pid) {
    }
    ~MotorController() {}

    bool setup() override;
    void setSpeed(const int16_t percent) override;
    uint32_t getSpeed() override;
    void stop() override;
    bool enable() override;
    bool disable() override;

   private:
    PWMInterface* pwm;
    DigitalGpioInterface* _enable;
    PID* pid;
};