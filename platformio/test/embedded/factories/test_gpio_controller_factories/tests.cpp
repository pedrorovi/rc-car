#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include <tests.h>
#include "debug_factory.h"
#include "digital_gpio_controller_factories.h"

Debug* debug = nullptr;

void setUp() {}
void tearDown() {}

void test_toggle_red_led() {
    debug = getDebugFactory();

    debug->trace("Starting test_toggle_red_led");
    DigitalGpioInterface* pin = getLedRedFactory();
    pin->digitalWrite(0);

    for (int i = 0; i < 10; i++) {
        pin->toggle();
        TEST_ASSERT_EQUAL_MESSAGE(1, pin->digitalRead(), "State is not the expected: 1");
        debug->trace("Red LED toggled to 1");
        delay_milliseconds(100);
        pin->toggle();
        TEST_ASSERT_EQUAL_MESSAGE(0, pin->digitalRead(), "State is not the expected: 0");
        debug->trace("Red LED toggled to 0");
        delay_milliseconds(100);
    }
}

void test_toggle_green_led() {
    DigitalGpioInterface* pin = getLedGreenFactory();
    debug->trace("Starting test_toggle_green_led");
    pin->digitalWrite(0);
    for (int i = 0; i < 10; i++) {
        pin->toggle();
        TEST_ASSERT_EQUAL_MESSAGE(1, pin->digitalRead(), "State is not the expected: 1");
        debug->trace("Green LED toggled to 1");
        delay_milliseconds(100);
        pin->toggle();
        TEST_ASSERT_EQUAL_MESSAGE(0, pin->digitalRead(), "State is not the expected: 0");
        debug->trace("Green LED toggled to 0");
        delay_milliseconds(100);
    }
}

void test_toggle_motor_enable() {
    DigitalGpioInterface* pin = getMotorEnableFactory();
    debug->trace("Starting test_toggle_motor_enable");
    pin->digitalWrite(0);
    for (int i = 0; i < 10; i++) {
        pin->toggle();
        TEST_ASSERT_EQUAL_MESSAGE(1, pin->digitalRead(), "State is not the expected: 1");
        debug->trace("Motor Enable toggled to 1");
        delay_milliseconds(100);
        pin->toggle();
        TEST_ASSERT_EQUAL_MESSAGE(0, pin->digitalRead(), "State is not the expected: 0");
        debug->trace("Motor Enable toggled to 0");
        delay_milliseconds(100);
    }
}
