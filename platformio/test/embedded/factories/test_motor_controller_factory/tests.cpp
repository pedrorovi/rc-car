#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"
#include "motor_controller_factory.h"

// Implements
#include <tests.h>

MotorInterface* motor = nullptr;

void setUp() {}
void tearDown() {}

void test_setup() {
    motor = getMotorInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(motor, "Motor is null");
    const bool ok = motor->setup();
    TEST_ASSERT_TRUE_MESSAGE(ok, "Motor setup failed");
    motor->setSpeed(0);
}

void test_move_forward() {
    const uint32_t start_ms = HAL_GetTick();
    uint32_t last_ms = start_ms;
    while (HAL_GetTick() - start_ms < 1000) {
        if (HAL_GetTick() - last_ms > 100) {
            motor->setSpeed(80);
            last_ms = HAL_GetTick();
        }
    }

    motor->stop();
    delay_seconds(2);
}

void test_move_backward() {
    const uint32_t start_ms = HAL_GetTick();
    uint32_t last_ms = start_ms;
    while (HAL_GetTick() - start_ms < 1000) {
        if (HAL_GetTick() - last_ms > 100) {
            motor->setSpeed(-100);
            last_ms = HAL_GetTick();
        }
    }
    motor->stop();
    delay_seconds(2);
}

void test_stop() {
    motor->stop();
}