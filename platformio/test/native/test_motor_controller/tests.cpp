#include <string.h>
#include <unity.h>

#include <motor_controller.h>
#include "motor_controller_factory.h"

#include <test_utils.h>
// Implements
#include <tests.h>

void setUp() {}
void tearDown() {}

void test_motor_setup() {
    MotorInterface* motor = getMotorInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(motor, "Motor is not null");
    TEST_ASSERT_TRUE_MESSAGE(motor->setup(), "Motor setup failed");
}

void test_motor_set_speed(void) {
    MotorInterface* motor = getMotorInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(motor, "Motor is not null");
    // TEST_ASSERT_TRUE_MESSAGE(motor->setup(), "Motor setup failed");
    motor->setSpeed(1000);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1220, motor->getSpeed(), "Motor speed is wrong");
}

void test_motor_get_speed(void) {
    MotorInterface* motor = getMotorInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(motor, "Motor is not null");
    TEST_ASSERT_TRUE_MESSAGE(motor->setup(), "Motor setup failed");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1500, motor->getSpeed(), "Motor speed is wrong");
    motor->setSpeed(1000);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1200, motor->getSpeed(), "Motor speed is wrong");
}

void test_motor_stop(void) {
    MotorInterface* motor = getMotorInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(motor, "Motor is not null");
    TEST_ASSERT_TRUE_MESSAGE(motor->setup(), "Motor setup failed");
    motor->setSpeed(1000);
    motor->stop();
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1500, motor->getSpeed(), "Motor speed is wrong");
}
