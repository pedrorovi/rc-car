#include <unity.h>

#include <test_utils.h>
#include <tests.h>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    //  Just an indicator that the tests have end.
    UNITY_END();

    return 0;
}