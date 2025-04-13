#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"
#include "pwm_hal.h"
#include "stdio.h"
#include "string.h"

// Implements
#include <tests.h>

extern UART_HandleTypeDef huart2;

PwmHal* pwm[2] = {nullptr, nullptr};

void setUp() {
    if (pwm[0] == nullptr) {
        pwm[0] = new PwmHal(1);
    }
    if (pwm[1] == nullptr) {
        pwm[1] = new PwmHal(4);
    }
}
void tearDown() {}

void test_pwm_1() {
    TEST_ASSERT_TRUE_MESSAGE(pwm[0]->start(), "Failed to start PwmHal");
    pwm[0]->updateDuty(1500);
    HAL_Delay(100);
    uint32_t duty = pwm[0]->getDuty();
    const uint16_t delta = 200;
    for (uint16_t offset = 0; offset < delta; offset++) {
        duty -= 1;
        pwm[0]->updateDuty(duty);
        HAL_Delay(20);
    }
    const char* msg = "Speed reduced\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 1000);

    pwm[0]->updateDuty(1500);
    duty = pwm[0]->getDuty();
    HAL_Delay(1000);

    for (uint16_t offset = 0; offset < delta; offset++) {
        duty += 1;
        pwm[0]->updateDuty(duty);
        HAL_Delay(20);
    }
    msg = "Speed increased\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 1000);

    pwm[0]->updateDuty(1500);
    HAL_Delay(100);

    pwm[0]->updateDuty(0);

    pwm[0]->stop();
}

void test_pwm_2() {
    TEST_ASSERT_TRUE_MESSAGE(pwm[1]->start(), "Failed to start PwmHal");
    pwm[1]->updateDuty(1500);
    HAL_Delay(500);

    pwm[1]->updateDuty(1200);
    HAL_Delay(500);
    pwm[1]->updateDuty(1800);
    HAL_Delay(500);

    pwm[1]->updateDuty(1500);
    HAL_Delay(50);
    pwm[1]->updateDuty(0);

    pwm[1]->stop();
}