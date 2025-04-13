#include "stepper_controller_factory.h"

#include "pwm_hal.h"
#include "stepper_controller.h"

static const uint8_t PWM_CHANNEL = 4;

static PwmHal* pwm = nullptr;

static StepperController* stepper = nullptr;

StepperInterface* getStepperInterfaceFactory() {
    if (stepper == nullptr) {
        pwm = new PwmHal(PWM_CHANNEL);
        stepper = new StepperController(pwm);
    }
    return stepper;
}
