#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_toggle_red_led);
    RUN_TEST(test_toggle_green_led);
    RUN_TEST(test_toggle_motor_enable);
    //  Just an indicator that the tests have end.
    UNITY_END();

    while (1)
        flash_leds();
}