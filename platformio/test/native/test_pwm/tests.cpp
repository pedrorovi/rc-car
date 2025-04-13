#include <string.h>
#include <unity.h>

#include <test_utils.h>
#include "pwm_hal.h"
// Implements
#include <tests.h>

void setUp() {}
void tearDown() {}

void test_start(void) {
    PwmHal* pwm = new PwmHal(1);
    TEST_ASSERT_TRUE(pwm->start());
}
void test_getDuty(void) {
    PwmHal* pwm = new PwmHal(1);
    pwm->start();
    pwm->updateDuty(1000);
    TEST_ASSERT_TRUE(pwm->getDuty() == 1000);
}
