#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"

#include "stdio.h"
// Implements
#include <tests.h>

void setUp() {}
void tearDown() {}

extern UART_HandleTypeDef huart2;

void test_setup(void) {
    // HAL_Init();
    // SystemClock_Config();
    // // MX_GPIO_Init();

    // MX_USART2_UART_Init();
}

void test_write(void) {
    HAL_Delay(1000);
    for (int i = 1; i <= 10; i++) {
        const char* msg_fmt = "Hello, World %i!\r\n";
        char msg[50];
        sprintf(msg, msg_fmt, i);
        HAL_StatusTypeDef res = HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 1000);
        TEST_ASSERT_EQUAL_MESSAGE(HAL_OK, res, "Failed to write to UART");
        HAL_Delay(100);
    }
}