#include <string.h>
#include <unity.h>

#include <test_utils.h>

#include "debug_factory.h"
#include "ina219_factory.h"

// Implements
#include <tests.h>

Debug* debug = nullptr;

void setUp() {
    debug = getDebugFactory();
}

void tearDown() {}

void test_setup() {
    INA219_interface* ina = getINA219Interface();
    // ina->setCalibration_32V_2A();
    // ina->setCalibration_32V_1A();
    ina->setCalibration_16V_6A();
    // ina->setCalibration_16V_400mA();
    debug->debug("INA219 connected");
}

void test_read() {
    INA219_interface* ina = getINA219Interface();

    const float shuntVoltage = ina->getShuntVoltage_mV();
    const float busVoltage = ina->getBusVoltage_V();
    const float power = ina->getPower_mW();
    const float current = ina->getCurrent_mA();

    debug->debug("Shunt voltage: %.2f mV, Bus voltage: %.2f V, Power: %.2f mW, Current: %.2f mA", shuntVoltage,
                 busVoltage, power, current);

    TEST_ASSERT_TRUE_MESSAGE(shuntVoltage > 0, "Shunt voltage is zero");
    TEST_ASSERT_TRUE_MESSAGE(busVoltage > 0, "Bus voltage is zero");
    TEST_ASSERT_TRUE_MESSAGE(power > 0, "Power is zero");
    TEST_ASSERT_TRUE_MESSAGE(current > 0, "Current is zero");
}

void test_read_loop() {
    INA219_interface* ina = getINA219Interface();

    for (int i = 0; i < 100; i++) {
        const float shuntVoltage = ina->getShuntVoltage_mV();
        const float busVoltage = ina->getBusVoltage_V();
        const float power = ina->getPower_mW();
        const float current = ina->getCurrent_mA();

        debug->debug("Shunt voltage: %.2f mV, Bus voltage: %.2f V, Power: %.2f mW, Current: %.2f mA", shuntVoltage,
                     busVoltage, power, current);
        delay_milliseconds(500);
    }
}