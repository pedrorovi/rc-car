// Implements
#include <test_utils.h>

#include "app.h"

void delay_milliseconds(uint32_t milliseconds) {}
void delay_seconds(uint32_t seconds) {}
void flash_leds() {
    GPIO_InitTypeDef GPIO_InitStruct = {GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0};
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(500);
}