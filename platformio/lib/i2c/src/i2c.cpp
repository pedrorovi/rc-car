#include "i2c.h"

#include "app.h"
#include "stm32l4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

I2C::I2C() {}

bool I2C::begin() {
    HAL_I2C_MspInit(&hi2c1);
    MX_I2C1_Init();
    return true;
}

bool I2C::write(const uint8_t address, uint8_t* data, const uint8_t length) {
    return HAL_I2C_Master_Transmit(&hi2c1, address, data, length, 1000) == HAL_OK;
}

bool I2C::writeReg(const uint8_t address, const uint8_t reg, uint8_t* data, const uint8_t length) {
    return HAL_I2C_Mem_Write(&hi2c1, address, reg, I2C_MEMADD_SIZE_8BIT, data, length, 1000) == HAL_OK;
}

bool I2C::read(const uint8_t address, uint8_t* data, const uint8_t length) {
    return HAL_I2C_Master_Receive(&hi2c1, address, data, length, 1000) == HAL_OK;
}

bool I2C::readReg(const uint8_t address, const uint8_t reg, uint8_t* data, const uint8_t length) {
    return HAL_I2C_Mem_Read(&hi2c1, address, reg, I2C_MEMADD_SIZE_8BIT, data, length, 1000) == HAL_OK;
}

bool I2C::isConnected(const uint8_t address) {
    return HAL_I2C_IsDeviceReady(&hi2c1, address, 1, 1000) == HAL_OK;
}

bool I2C::end() {
    HAL_I2C_MspDeInit(&hi2c1);
    return HAL_I2C_DeInit(&hi2c1) == HAL_OK;
}
