#include "pwm_hal.h"

#include <stdio.h>

PwmHal::PwmHal(const uint8_t chnl) : chnl(chnl), duty(0), frequency(0) {}

#ifndef NATIVE

#include "app.h"

extern TIM_HandleTypeDef htim1;

bool PwmHal::start() {
    switch (chnl) {
        case 1:
            return HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1) == HAL_OK;
        case 4:
            return HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4) == HAL_OK;
        default:
            return false;
    }
}

void PwmHal::stop() {
    switch (chnl) {
        case 1:
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            break;
        case 4:
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
            break;
        default:
            break;
    }
}

void PwmHal::updateDuty(const uint32_t duty) {
    this->duty = duty;
    switch (chnl) {
        case 1:
            htim1.Instance->CCR1 = duty;
            break;
        case 4:
            htim1.Instance->CCR4 = duty;
            break;
        default:
            break;
    }
}

uint32_t PwmHal::getDuty() {
    return duty;
}

#else

bool PwmHal::start() {
    switch (chnl) {
        case 1:
            return true;
        case 4:
            return true;
        default:
            return false;
    }
    return false;
}

void PwmHal::stop() {}

void PwmHal::updateDuty(const uint32_t duty) {
    this->duty = duty;
}

uint32_t PwmHal::getDuty() {
    return duty;
}

#endif