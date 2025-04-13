#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_start);
    RUN_TEST(test_getDuty);
    //  Just an indicator that the tests have end.
    UNITY_END();

    return 0;
}