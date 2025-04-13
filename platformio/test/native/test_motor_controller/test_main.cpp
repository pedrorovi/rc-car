#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_motor_setup);
    RUN_TEST(test_motor_set_speed);
    RUN_TEST(test_motor_get_speed);
    RUN_TEST(test_motor_stop);
    //  Just an indicator that the tests have end.
    UNITY_END();

    return 0;
}