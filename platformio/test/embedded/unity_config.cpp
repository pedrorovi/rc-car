#include "unity_config.h"

#include "app.h"

// #include "debug_factory.h"
#include "string.h"

extern UART_HandleTypeDef huart2;

void unityOutputStart() {
    setup_hal();

    // HAL_Init();
    // SystemClock_Config();
    // HAL_Delay(1000);
    // getDebugFactory()->print("Unity test started");
    HAL_Delay(1000);
    HAL_UART_Transmit(&huart2, (uint8_t*)"Unity test started\n", strlen("Unity test started\n"), 1000);
}

void unityOutputChar(char c) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&c, 1, 1000);
    // getDebugFactory()->print(c);
}

void unityOutputFlush() {
    // getDebugFactory()->print("\r\n");
}

void unityOutputComplete() {}
