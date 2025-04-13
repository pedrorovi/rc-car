#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_setup);
    RUN_TEST(test_read);
    // RUN_TEST(test_read_loop);
    //  Just an indicator that the tests have end.
    UNITY_END();

    while (1)
        flash_leds();
}