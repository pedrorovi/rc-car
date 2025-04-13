#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "mppt_controller.h"
#include "stdio.h"

// Implements
#include <tests.h>

void setUp() {}
void tearDown() {}

struct GivenData_t {
    float voltage;  
    float current;
};

struct ThenData_t {
    uint16_t pwm;
};

void test_mppt() {
    const uint16_t MIN_PWM = 20;
    const uint16_t MAX_PWM = 80;
    const uint16_t PWM_STEP = 1;
    const float GIVEN_VOLTAGES[] = {15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0};
    const float GIVEN_CURRENTS[] = {2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0};
    const uint16_t EXPECTED_PWMS[] = {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};
    const uint32_t LEN = sizeof(GIVEN_VOLTAGES) / sizeof(GIVEN_VOLTAGES[0]);

    uint32_t lookup_index = 0;

    MPPT mppt(MIN_PWM, MAX_PWM, PWM_STEP);

    for (uint32_t i = 0; i < LEN; i++) {
        GivenData_t given = {GIVEN_VOLTAGES[lookup_index], GIVEN_CURRENTS[lookup_index]};
        ThenData_t then = {mppt.update(given.voltage, given.current)};
        printf("Pwm: %i\n", then.pwm);
        TEST_ASSERT_GREATER_THAN(MIN_PWM, then.pwm);
        TEST_ASSERT_LESS_THAN(MAX_PWM, then.pwm);
        TEST_ASSERT_EQUAL_UINT16_MESSAGE(EXPECTED_PWMS[lookup_index], then.pwm, "Pwm value is not correct");
        lookup_index++;
    }
}