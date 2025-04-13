#include "servo_controller.h"

#include "stdio.h"

bool ServoController::setup() {
    const bool ok = pwm->start();
    if (!ok) {
        return false;
    }

    pwm->updateDuty(1500);
    return true;
}

void ServoController::setDirection(const uint32_t direction) {
    pwm->updateDuty(direction);
}

uint32_t ServoController::getDirection() {
    return pwm->getDuty();
}

void ServoController::straight() {
    pwm->updateDuty(1500);
}
