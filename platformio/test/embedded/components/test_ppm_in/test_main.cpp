#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ppm_in_0);
    RUN_TEST(test_ppm_in_1);
    //  Just an indicator that the tests have end.
    UNITY_END();

    while (1)
        flash_leds();
}