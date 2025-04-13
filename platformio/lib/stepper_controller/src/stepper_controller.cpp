#include "stepper_controller.h"

#include "stdio.h"

bool StepperController::setup() {
    const bool ok = pwm->start();
    if (!ok) {
        return false;
    }

    pwm->updateDuty(1500);
    return true;
}

void StepperController::setDirection(const uint32_t direction) {
    pwm->updateDuty(direction);
}

uint32_t StepperController::getDirection() {
    return pwm->getDuty();
}

void StepperController::straight() {
    pwm->updateDuty(1500);
}
