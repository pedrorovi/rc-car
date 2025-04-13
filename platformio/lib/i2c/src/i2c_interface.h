#pragma once

#include "stdint.h"

struct I2CInterface {
    virtual bool begin() = 0;
    virtual bool write(const uint8_t address, uint8_t* data, const uint8_t length) = 0;
    virtual bool writeReg(const uint8_t address, const uint8_t reg, uint8_t* data, const uint8_t length) = 0;
    virtual bool read(const uint8_t address, uint8_t* data, const uint8_t length) = 0;
    virtual bool readReg(const uint8_t address, const uint8_t reg, uint8_t* data, const uint8_t length) = 0;
    virtual bool isConnected(const uint8_t address) = 0;
    virtual bool end() = 0;
};