#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include <INA219.h>
#include "app.h"
#include "i2c.h"

#include "stdio.h"

// Implements
#include <tests.h>

INA219* ina = nullptr;
I2C* i2c = nullptr;
extern UART_HandleTypeDef huart2;

void setUp() {
    if (i2c == nullptr) {
        i2c = new I2C();
        TEST_ASSERT_TRUE_MESSAGE(i2c->begin(), "I2C cannot begin");
        for (uint8_t address = 0x01; address <= 0x7F; address++) {
            const bool ok = i2c->isConnected(address << 1);
            HAL_Delay(10);
            if (ok) {
                const char* msg = "I2C connected 0x%02x\r\n";
                char buffer[128];
                sprintf(buffer, msg, address);
                HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);
                HAL_Delay(100);
                break;
            }
        }
    }

    if (ina == nullptr) {
        ina = new INA219(i2c);
    }
}
void tearDown() {}

void test_setup() {
    // ina->setCalibration_32V_2A();
    // ina->setCalibration_32V_1A();
    ina->setCalibration_16V_6A();
    // ina->setCalibration_16V_400mA();

    const char* msg = "INA219 connected\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 1000);
    HAL_Delay(100);
}

void test_read() {
    const float shuntVoltage = ina->getShuntVoltage_mV();
    const float busVoltage = ina->getBusVoltage_V();
    const float power = ina->getPower_mW();
    const float current = ina->getCurrent_mA();

    const char* fmt = "Shunt voltage: %.2f mV, Bus voltage: %.2f V, Power: %.2f mW, Current: %.2f mA\r\n";
    char buffer[128];
    snprintf(buffer, sizeof(buffer), fmt, shuntVoltage, busVoltage, power, current);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);

    TEST_ASSERT_TRUE_MESSAGE(shuntVoltage > 0, "Shunt voltage is zero");
    TEST_ASSERT_TRUE_MESSAGE(busVoltage > 0, "Bus voltage is zero");
    TEST_ASSERT_TRUE_MESSAGE(power > 0, "Power is zero");
    TEST_ASSERT_TRUE_MESSAGE(current > 0, "Current is zero");
}

void test_read_loop() {
    while (true) {
        const float shuntVoltage = ina->getShuntVoltage_mV();
        const float busVoltage = ina->getBusVoltage_V();
        const float power = ina->getPower_mW();
        const float current = ina->getCurrent_mA();

        const char* fmt = "Shunt voltage: %.2f mV, Bus voltage: %.2f V, Power: %.2f mW, Current: %.2f mA\r\n";
        char buffer[128];
        snprintf(buffer, sizeof(buffer), fmt, shuntVoltage, busVoltage, power, current);
        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);
        HAL_Delay(1000);
    }
}