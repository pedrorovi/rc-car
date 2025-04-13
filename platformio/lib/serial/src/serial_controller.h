#pragma once

#include "ringbuffer.h"
#include "serial_interface.h"

class SerialController : public SerialInterface_t {
   public:
    SerialController(const SerialPort serial_num);
    ~SerialController() override = default;

    void begin(const uint32_t baudrate) override;
    void end() override;
    void write(const char data) override;
    void write(const uint8_t data) override;
    void write(const char* data) override;
    void write(const uint8_t* data) override;
    void write(const char* data, const uint32_t length) override;
    void write(const uint8_t* data, const uint32_t length) override;
    void read(uint8_t* data, const uint32_t length) override;
    bool available() override;

   private:
    SerialPort serial_num;
    ring_buffer_t ring_buffer;
    uint8_t buffer[1024];
};