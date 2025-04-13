#include "servo_controller_factory.h"

#include "pwm_hal.h"
#include "servo_controller.h"

static const uint8_t PWM_CHANNEL = 4;

static PwmHal* pwm = nullptr;

static ServoController* servo = nullptr;

ServoInterface* getServoInterfaceFactory() {
    if (servo == nullptr) {
        pwm = new PwmHal(PWM_CHANNEL);
        servo = new ServoController(pwm);
    }
    return servo;
}
