#include "stdio.h"

#include "app.h"

extern UART_HandleTypeDef huart2;

void _putchar(char character) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&character, 1, 1000);
}
