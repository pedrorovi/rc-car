#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup);
    RUN_TEST(test_move_forward);
    RUN_TEST(test_move_backward);
    RUN_TEST(test_stop);
    //  Just an indicator that the tests have end.
    UNITY_END();

    while (1)
        flash_leds();
}