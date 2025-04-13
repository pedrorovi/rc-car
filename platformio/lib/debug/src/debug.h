#pragma once

#include "serial_interface.h"

class Debug {
   public:
    Debug(SerialInterface_t* serial_interface);
    ~Debug() = default;

    void trace(const char* format, ...);
    void debug(const char* format, ...);
    void info(const char* format, ...);
    void warning(const char* format, ...);
    void error(const char* format, ...);
    void print(const char* message);
    void print(const char c);

   private:
    void send(const char* message, const char* color, const char* tag);

    SerialInterface_t* serial_interface;
};
