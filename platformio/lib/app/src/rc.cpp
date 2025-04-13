#include "rc.h"

#include "app.h"
#include "cmsis_os.h"
#include "system_controller.h"
#include "system_factory.h"
#include "timers.h"

static System* system;

static osThreadId_t mpptTask;
static osThreadId_t loopTask;

static const osThreadAttr_t mpptTask_attributes = {
    "mpptTask",                      // name
    0,                               // attr_bits
    NULL,                            // cb_mem
    0,                               // cb_size
    NULL,                            // stack_mem
    1024,                            // stack_size
    (osPriority_t)osPriorityNormal,  // priority
    0,                               // tz_module
    0                                // reserved
};

static const osThreadAttr_t loopTask_attributes = {
    "loopTask",                      // name
    0,                               // attr_bits
    NULL,                            // cb_mem
    0,                               // cb_size
    NULL,                            // stack_mem
    1024 * 4,                        // stack_size
    (osPriority_t)osPriorityNormal,  // priority
    0,                               // tz_module
    0                                // reserved
};

// Declare a mutex handle
static osMutexId_t hardwareMutex;
static const osMutexAttr_t hardwareMutex_attributes = {
    "hardwareMutex",  // name
    0,                // attr_bits
    NULL,             // cb_mem
    0                 // cb_size
};

static void mpptLoop(void* argument) {
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for (;;) {
        if (osMutexAcquire(hardwareMutex, 100) == osOK) {
            mpptLoop(system);
            osMutexRelease(hardwareMutex);  // Release the mutex
        }
        osDelay(100);
    }
    /* USER CODE END 5 */
}

static void stepperTask(void* argument) {
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for (;;) {
        if (osMutexAcquire(hardwareMutex, 100) == osOK) {
            updateStepperLoop(system);
            osMutexRelease(hardwareMutex);
        }
        osDelay(1);
    }
    /* USER CODE END 5 */
}

static void vTimerCallback(TimerHandle_t xTimer) {
    // const char* logMessage = "Toggling green LED";
    // system->getDebug()->info(logMessage);
    system->getLedGreen()->toggle();
}

void setupApp() {
    HAL_Init();
    SystemClock_Config();
    osKernelInitialize();

    setup_hal();

    system = getSystem();
    if (!setupSystem(system)) {
        system->getDebug()->error("Failed to setup system");
        Error_Handler();
    }

    extern size_t xPortGetFreeHeapSize(void);
    system->getDebug()->info("Free heap size before task creation: %d", xPortGetFreeHeapSize());

    // Initialize the mutex
    hardwareMutex = osMutexNew(&hardwareMutex_attributes);
    if (hardwareMutex == NULL) {
        system->getDebug()->error("Failed to create mutex");
        Error_Handler();
    }

    mpptTask = osThreadNew(mpptLoop, NULL, &loopTask_attributes);
    loopTask = osThreadNew(stepperTask, NULL, &loopTask_attributes);

    // // Create and start the timer
    // TimerHandle_t xTimer = xTimerCreate("MyTimer", pdMS_TO_TICKS(500), pdTRUE, 0, vTimerCallback);
    // if (xTimer == NULL) {
    //     system->getDebug()->error("Failed to create timer");
    //     Error_Handler();
    // }
    // if (xTimerStart(xTimer, 0) != pdPASS) {
    //     system->getDebug()->error("Failed to start timer");
    //     Error_Handler();
    // }

    // Check heap size after creating tasks
    system->getDebug()->info("Free heap size after task creation: %d", xPortGetFreeHeapSize());

    osKernelStart();
}

void loopApp() {
    while (1)
        ;
}
