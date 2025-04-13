#pragma once

#include "i2c_interface.h"

class I2C : public I2CInterface {
   public:
    I2C();
    bool begin() override;
    bool write(const uint8_t address, uint8_t* data, const uint8_t length) override;
    bool writeReg(const uint8_t address, const uint8_t reg, uint8_t* data, const uint8_t length) override;
    bool read(const uint8_t address, uint8_t* data, const uint8_t length) override;
    bool readReg(const uint8_t address, const uint8_t reg, uint8_t* data, const uint8_t length) override;
    bool isConnected(const uint8_t address) override;
    bool end() override;

   private:
};