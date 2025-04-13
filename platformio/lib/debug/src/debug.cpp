#include "debug.h"

#include <cstring>

#define COLOR_RESET "\033[0m"
#define COLOR_TRACE "\033[36m"    // Cyan
#define COLOR_DEBUG "\033[34m"    // Blue
#define COLOR_INFO "\033[32m"     // Green
#define COLOR_WARNING "\033[33m"  // Yellow
#define COLOR_ERROR "\033[31m"    // Red

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "debug.h"

Debug::Debug(SerialInterface_t* serial_interface) {
    this->serial_interface = serial_interface;
}

void Debug::send(const char* message, const char* color, const char* tag) {
    serial_interface->write(color);
    serial_interface->write(tag);
    serial_interface->write(message);
    serial_interface->write(COLOR_RESET);
    serial_interface->write("\r\n");
}

void Debug::trace(const char* format, ...) {
#if LOG_LEVEL >= 5
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    send(buffer, COLOR_TRACE, "[TRACE] ");
#endif
}

void Debug::debug(const char* format, ...) {
#if LOG_LEVEL >= 4
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    send(buffer, COLOR_DEBUG, "[DEBUG] ");
#endif
}

void Debug::info(const char* format, ...) {
#if LOG_LEVEL >= 3
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    send(buffer, COLOR_INFO, "[INFO] ");
#endif
}

void Debug::warning(const char* format, ...) {
#if LOG_LEVEL >= 2
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    send(buffer, COLOR_WARNING, "[WARNING] ");
#endif
}

void Debug::error(const char* format, ...) {
#if LOG_LEVEL >= 1
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    send(buffer, COLOR_ERROR, "[ERROR] ");
#endif
}

void Debug::print(const char* message) {
#if LOG_LEVEL >= 1
    serial_interface->write(message);
#endif
}
void Debug::print(const char c) {
#if LOG_LEVEL >= 1
    serial_interface->write(c);
#endif
}