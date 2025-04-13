#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"
#include "stepper_controller_factory.h"

// Implements
#include <tests.h>

StepperInterface* stepper = nullptr;

void setUp() {}
void tearDown() {}

void test_setup() {
    stepper = getStepperInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(stepper, "stepper is null");
    const bool ok = stepper->setup();
    TEST_ASSERT_TRUE_MESSAGE(ok, "stepper setup failed");
    stepper->straight();
    delay_seconds(1);
}

void test_turn_right() {
    stepper->setDirection(2000);
    TEST_ASSERT_EQUAL_MESSAGE(2000, stepper->getDirection(), "stepper direction is not 2000");
    delay_seconds(1);
    stepper->straight();
    TEST_ASSERT_EQUAL_MESSAGE(1500, stepper->getDirection(), "stepper direction is not 1500");
    delay_seconds(1);
}
void test_turn_left() {
    stepper->setDirection(1000);
    TEST_ASSERT_EQUAL_MESSAGE(1000, stepper->getDirection(), "stepper direction is not 1000");
    delay_seconds(1);
    stepper->straight();
    TEST_ASSERT_EQUAL_MESSAGE(1500, stepper->getDirection(), "stepper direction is not 1500");
    delay_seconds(1);
}
void test_straight() {
    stepper->straight();
    TEST_ASSERT_EQUAL_MESSAGE(1500, stepper->getDirection(), "stepper direction is not 1500");
    delay_seconds(1);
}