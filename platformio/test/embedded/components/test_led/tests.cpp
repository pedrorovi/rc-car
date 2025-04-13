#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"

// Implements
#include <tests.h>

void setUp() {}

void tearDown() {}


static void test_led(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    TEST_ASSERT_EQUAL(GPIO_PIN_RESET, HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
    for (int i = 0; i < 10; i++) {
        HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);

        if (i % 2 == 0) {
            TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
        } else {
            TEST_ASSERT_EQUAL(GPIO_PIN_RESET, HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
        }
        HAL_Delay(100);
    }
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

void test_led_green() {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    test_led(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}

void test_led_red() {
    test_led(LED_RED_GPIO_Port, LED_RED_Pin);
}