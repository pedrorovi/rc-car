#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"
#include "servo_controller_factory.h"

// Implements
#include <tests.h>

ServoInterface* servo = nullptr;

void setUp() {}
void tearDown() {}

void test_setup() {
    servo = getServoInterfaceFactory();
    TEST_ASSERT_NOT_NULL_MESSAGE(servo, "servo is null");
    const bool ok = servo->setup();
    TEST_ASSERT_TRUE_MESSAGE(ok, "servo setup failed");
    servo->straight();
    delay_seconds(1);
}

void test_turn_right() {
    servo->setDirection(2000);
    TEST_ASSERT_EQUAL_MESSAGE(2000, servo->getDirection(), "servo direction is not 2000");
    delay_seconds(1);
    servo->straight();
    TEST_ASSERT_EQUAL_MESSAGE(1500, servo->getDirection(), "servo direction is not 1500");
    delay_seconds(1);
}
void test_turn_left() {
    servo->setDirection(1000);
    TEST_ASSERT_EQUAL_MESSAGE(1000, servo->getDirection(), "servo direction is not 1000");
    delay_seconds(1);
    servo->straight();
    TEST_ASSERT_EQUAL_MESSAGE(1500, servo->getDirection(), "servo direction is not 1500");
    delay_seconds(1);
}
void test_straight() {
    servo->straight();
    TEST_ASSERT_EQUAL_MESSAGE(1500, servo->getDirection(), "servo direction is not 1500");
    delay_seconds(1);
}