#include "ppm_in.h"

#include <stdio.h>
#include <string.h>
#include "app.h"
#include "debug_factory.h"

extern TIM_HandleTypeDef htim2;

#define TIMCLOCK 32000000
#define PRESCALAR 1

bool PPMIn::start() {
    switch (chnl) {
        case 1:
            // HAL_TIM_Base_MspInit(&htim2);
            getDebugFactory()->info("Starting channel 1");
            return HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1) == HAL_OK;
        case 2:
            // HAL_TIM_Base_MspInit(&htim2);
            getDebugFactory()->info("Starting channel 2");
            return HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2) == HAL_OK;
        default:
            getDebugFactory()->error("Invalid channel %d", chnl);
            return false;
    }
}

void PPMIn::stop() {
    switch (chnl) {
        case 1:
            HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);
            break;
        case 2:
            HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_2);
            break;
        default:
            break;
    }
}

float PPMIn::getPulseWidthUs() {
    return pulseWidthUs;
}

void PPMIn::updatePulseWidth() {
    if (isFirstCapture) {
        riseCapture = HAL_TIM_ReadCapturedValue(&htim2, chnl == 1 ? TIM_CHANNEL_1 : TIM_CHANNEL_2);
        // getDebugFactory()->trace("Rise capture: %u", riseCapture);
        isFirstCapture = false;
    } else {
        fallCapture = HAL_TIM_ReadCapturedValue(&htim2, chnl == 1 ? TIM_CHANNEL_1 : TIM_CHANNEL_2);
        // getDebugFactory()->trace("Fall capture: %u", fallCapture);
        if (fallCapture > riseCapture) {
            diff = fallCapture - riseCapture;
        } else {
            diff = (0xFFFFFFFF - riseCapture) + fallCapture;
        }
        const float refClock = TIMCLOCK / PRESCALAR;
        const float factor = 1000000 / refClock;

        pulseWidthUs = (float)diff * factor;
        riseCapture = fallCapture;
        isFirstCapture = true;
        // getDebugFactory()->trace("Pulse width: %.2f", pulseWidthUs);
    }
}
