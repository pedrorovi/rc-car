#include "watchdog_controller.h"

#include "app.h"
#include "stm32l4xx_hal.h"

extern IWDG_HandleTypeDef hiwdg;

void WatchdogController::setup() {
    // Start the watchdog timer with a timeout of 1 second
    MX_IWDG_Init();
}

void WatchdogController::refresh() {
    // Refresh the watchdog timer
    HAL_IWDG_Refresh(&hiwdg);
}