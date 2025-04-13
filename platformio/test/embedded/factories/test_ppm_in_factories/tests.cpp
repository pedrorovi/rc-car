#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "stdio.h"
#include "string.h"

#include "debug_factory.h"
#include "app.h"
#include "ppm_in_factory.h"
#include "stm32l4xx_hal.h"

// Implements
#include <tests.h>

Debug* debug;

void setUp() {
    HAL_Init();
    SystemClock_Config();
    HAL_MspInit();

    debug = getDebugFactory();
}

void tearDown() {}

PPMInInterface* motorPPMIn = nullptr;
PPMInInterface* servoPPMIn = nullptr;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    switch (htim->Channel) {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            if (motorPPMIn != nullptr) {
                // debug->debug("IRQ 1");
                motorPPMIn->updatePulseWidth();
            }
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            if (servoPPMIn != nullptr) {
                // debug->debug("IRQ 2");
                servoPPMIn->updatePulseWidth();
            }
            break;
        default:
            break;
    }
}

void test_ppm_in_0() {
    motorPPMIn = getMotorPPMInInterface();

    debug->info("Ppm 0");
    TEST_ASSERT_NOT_NULL(motorPPMIn);
    TEST_ASSERT_TRUE(motorPPMIn->start());
    debug->debug("PPM IN 0: started");

    for (int i = 0; i < 10; i++) {
        HAL_Delay(100);
        // debug->print("PPM IN 0: %.2f us", motorPPMIn->getPulseWidthUs());
        // TEST_ASSERT_TRUE(motorPPMIn->getPulseWidthUs() > 0);
    }
    debug->debug("PPM IN 0: stopping");
    motorPPMIn->stop();
    // TEST_ASSERT_TRUE(ppm->getPulseWidthUs() == 0);
}

void test_ppm_in_1() {
    servoPPMIn = getServoPPMInInterface();

    debug->info("Ppm 1");
    TEST_ASSERT_NOT_NULL(servoPPMIn);
    TEST_ASSERT_TRUE(servoPPMIn->start());

    for (int i = 0; i < 10; i++) {
        HAL_Delay(100);
        debug->info("PPM IN 1: %.2f us", servoPPMIn->getPulseWidthUs());
        // TEST_ASSERT_TRUE(servoPPMIn->getPulseWidthUs() > 0);
    }
    servoPPMIn->stop();
    // TEST_ASSERT_TRUE(servoPPMIn->getPulseWidthUs() == 0);
}
