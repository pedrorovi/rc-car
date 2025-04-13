#include "ppm_in_factory.h"

#include "ppm_in.h"

#include "stm32l4xx_hal.h"

static PPMInInterface* motorPPMIn = nullptr;
static PPMInInterface* stepperPPMIn = nullptr;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    switch (htim->Channel) {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            if (motorPPMIn != nullptr)
                motorPPMIn->updatePulseWidth();
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            if (stepperPPMIn != nullptr)
                stepperPPMIn->updatePulseWidth();
            break;
        default:
            break;
    }
}

PPMInInterface* getMotorPPMInInterface() {
    if (motorPPMIn == nullptr) {
        motorPPMIn = new PPMIn(1);
    }
    return motorPPMIn;
}

PPMInInterface* getStepperPPMInInterface() {
    if (stepperPPMIn == nullptr) {
        stepperPPMIn = new PPMIn(2);
    }
    return stepperPPMIn;
}
