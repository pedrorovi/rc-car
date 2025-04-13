#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_led_green);
    RUN_TEST(test_led_red);
    //  Just an indicator that the tests have end.
    UNITY_END();

    while (1)
        flash_leds();
}