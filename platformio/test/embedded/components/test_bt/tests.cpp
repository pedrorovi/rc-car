#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "app.h"

#include "stdio.h"
// Implements
#include <tests.h>

void setUp() {}
void tearDown() {}

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void test_setup(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    MX_USART1_UART_Init();
}

void test_write(void) {
    HAL_Delay(1000);
    for (int i = 0; i < 5; i++) {
        const char* msg_fmt = "Hello, World %i!\r\n";
        char msg[50];
        sprintf(msg, msg_fmt, i);
        HAL_StatusTypeDef res = HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 1000);
        TEST_ASSERT_EQUAL_MESSAGE(HAL_OK, res, "Failed to write to UART");
        HAL_Delay(100);
    }
}

int uart_available(UART_HandleTypeDef* huart) {
    return __HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE);
}

void test_read(void) {
    uint8_t buffer[50];
    uint8_t index = 0;
    while (true) {
        if (uart_available(&huart1)) {
            uint8_t ch;
            HAL_StatusTypeDef res = HAL_UART_Receive(&huart1, &ch, 1, 1000);
            if (res == HAL_OK) {
                buffer[index++] = ch;
                if (ch == '\n' || index >= sizeof(buffer) - 1) {
                    buffer[index] = '\0';  // Null-terminate the string
                    const char* msg = "Received: %s\r\n";
                    char out[100];
                    sprintf(out, msg, buffer);
                    HAL_UART_Transmit(&huart2, (uint8_t*)out, strlen(out), 1000);
                    index = 0;  // Reset the buffer index
                }
            }
        }
    }
}
