#include "digital_gpio_controller.h"

#include "app.h"
#include "stm32l4xx_hal.h"

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
void MX_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : LED_GREEN_Pin LED_RED_Pin MOTOR_EN_Pin */
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/**
 * @brief Helper function to get GPIO_TypeDef* from Port enum
 */
static GPIO_TypeDef* getGPIOPort(Port port) {
    switch (port) {
        case Port::A:
            return GPIOA;
        case Port::B:
            return GPIOB;
        case Port::C:
            return GPIOC;
        case Port::H:
            return GPIOH;
        default:
            return nullptr;  // Error case
    }
}

void DigitalGpioController::setup() {
    GPIO_TypeDef* gpioPort = getGPIOPort(pin_.p);
    if (gpioPort) {
        MX_GPIO_Init(gpioPort, pin_.pin);
    }
}

void DigitalGpioController::digitalWrite(int value) {
    GPIO_TypeDef* gpioPort = getGPIOPort(pin_.p);
    if (gpioPort) {
        HAL_GPIO_WritePin(gpioPort, pin_.pin, (GPIO_PinState)value);
    }
}

int DigitalGpioController::digitalRead() {
    GPIO_TypeDef* gpioPort = getGPIOPort(pin_.p);
    if (gpioPort) {
        return HAL_GPIO_ReadPin(gpioPort, pin_.pin);
    }
    return -1;  // Error
}

void DigitalGpioController::toggle() {
    GPIO_TypeDef* gpioPort = getGPIOPort(pin_.p);
    if (gpioPort) {
        HAL_GPIO_TogglePin(gpioPort, pin_.pin);
    }
}