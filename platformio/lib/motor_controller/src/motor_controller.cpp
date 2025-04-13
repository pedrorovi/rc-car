#include "motor_controller.h"

#include "stdio.h"

#include "debug_factory.h"

static int32_t map(const int32_t x,
                   const int32_t in_min = -100,
                   const int32_t in_max = 100,
                   const int32_t out_min = 1000,
                   const int32_t out_max = 2000) {
    return (x - in_min) * ((out_max - out_min) / (in_max - in_min)) + out_min;
}

bool MotorController::setup() {
    _enable->setup();

    const bool ok = pwm->start();
    if (!ok) {
        return false;
    }
    pwm->updateDuty(map(0));
    return true;
}

void MotorController::setSpeed(const int16_t percent) {
    const uint32_t current = pwm->getDuty();
    const int32_t sp = map(percent);
    const double duty = 1500 + pid->calculate(sp, current);
    getDebugFactory()->debug("MotorController::setSpeed SP: %i Duty: %.2f, Speed: %i, Current: %i", sp, duty, percent,
                             current);
    pwm->updateDuty((uint32_t)(duty));
}

uint32_t MotorController::getSpeed() {
    return pwm->getDuty();
}

void MotorController::stop() {
    pwm->updateDuty(map(0));
}

bool MotorController::enable() {
    _enable->digitalWrite(1);
    return _enable->digitalRead() == 1;
}
bool MotorController::disable() {
    _enable->digitalWrite(0);
    return _enable->digitalRead() == 0;
}
