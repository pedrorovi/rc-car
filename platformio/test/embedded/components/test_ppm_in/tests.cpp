#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"
#include "debug_factory.h"
#include "ppm_in.h"
#include "stdio.h"
#include "string.h"

// Implements
#include <tests.h>

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef* htim2;

PPMIn* ppmIn[2] = {nullptr, nullptr};
bool isPulseWidthUpdated[2] = {false, false};

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    switch (htim->Channel) {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            isPulseWidthUpdated[0] = true;
            ppmIn[0]->updatePulseWidth();
            // HAL_UART_Transmit(&huart2, (uint8_t*)"Callback chn1\n", strlen("Callback chn1\n"), 1000);
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            isPulseWidthUpdated[1] = true;
            ppmIn[1]->updatePulseWidth();
            // HAL_UART_Transmit(&huart2, (uint8_t*)"Callback chn2\n", strlen("Callback chn2\n"), 1000);
            break;
        default:
            break;
    }
}

Debug* debug;

void setUp() {
    if (ppmIn[0] == nullptr) {
        ppmIn[0] = new PPMIn(1);
    }

    if (ppmIn[1] == nullptr) {
        ppmIn[1] = new PPMIn(2);
    }
}

void tearDown() {}

void test_ppm_in_0() {
    // debug = getDebugFactory();

    TEST_ASSERT_TRUE_MESSAGE(ppmIn[0]->start(), "Failed to start PPMIn[0]");

    const uint32_t START = HAL_GetTick();

    while (HAL_GetTick() - START < 1000) {
        HAL_Delay(10);
        if (isPulseWidthUpdated[0]) {
            const float pulseWidthMs = ppmIn[0]->getPulseWidthUs() / 1000;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.6, 1.5, pulseWidthMs, "Pulse width is not within 0.6 of 1.5");
            // debug->info("PPM IN 0: %.2f us", pulseWidthMs);
            const char* fmt = "PPM IN 0: %.2f us\n";
            char buffer[50];
            sprintf(buffer, fmt, pulseWidthMs);
            HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);
            // HAL_UART_Transmit(&huart2, (uint8_t*)"Callback loop\n", strlen("Callback loop\n"), 1000);
            isPulseWidthUpdated[0] = false;
        } /* else {
            HAL_Delay(10);
            HAL_UART_Transmit(&huart2, (uint8_t*)"Loop\n", strlen("Loop\n"), 1000);
        } */
    }
}

void test_ppm_in_1() {
    // debug = getDebugFactory();

    TEST_ASSERT_TRUE_MESSAGE(ppmIn[1]->start(), "Failed to start PPMIn[1]");

    const uint32_t START = HAL_GetTick();

    while (HAL_GetTick() - START < 1000) {
        HAL_Delay(10);
        if (isPulseWidthUpdated[1]) {
            const float pulseWidthMs = ppmIn[1]->getPulseWidthUs() / 1000;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.6, 1.5, pulseWidthMs, "Pulse width is not within 0.6 of 1.5");
            const char* fmt = "PPM IN 1: %.2f us\n";
            char buffer[50];
            sprintf(buffer, fmt, pulseWidthMs);
            HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);
            // debug->info("PPM IN 1: %.2f us", pulseWidthMs);

            // HAL_UART_Transmit(&huart2, (uint8_t*)"Callback loop\n", strlen("Callback loop\n"), 1000);
            isPulseWidthUpdated[1] = false;
        } /* else {
            HAL_Delay(10);
            HAL_UART_Transmit(&huart2, (uint8_t*)"Loop\n", strlen("Loop\n"), 1000);
        } */
    }
}
