#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup);
    RUN_TEST(test_turn_right);
    RUN_TEST(test_turn_left);
    RUN_TEST(test_straight);
    //  Just an indicator that the tests have end.
    UNITY_END();

    while (1)
        flash_leds();
}