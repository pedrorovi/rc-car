#pragma once

#include "stdint.h"

enum class SerialPort : uint8_t { UART = 0, BLUETOOTH = 1 };

struct SerialInterface_t {
    virtual void begin(const uint32_t baudrate) = 0;
    virtual void end() = 0;
    virtual void write(const char data) = 0;
    virtual void write(const uint8_t data) = 0;
    virtual void write(const char* data) = 0;
    virtual void write(const uint8_t* data) = 0;
    virtual void write(const char* data, const uint32_t length) = 0;
    virtual void write(const uint8_t* data, const uint32_t length) = 0;
    virtual void read(uint8_t* data, const uint32_t length) = 0;
    virtual bool available() = 0;

    virtual ~SerialInterface_t() = default;
};