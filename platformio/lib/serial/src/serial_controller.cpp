#include "serial_controller.h"

#include <cstring>
#include "app.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
static constexpr uint32_t TIMEOUT_MS = 1000;

SerialController::SerialController(const SerialPort serial_num) : serial_num(serial_num) {}

void SerialController::begin(const uint32_t baudrate) {
    ring_buffer_init(&ring_buffer, (char*)(buffer), sizeof(buffer));
    switch (serial_num) {
        case SerialPort::UART:
            MX_USART1_UART_Init();
            HAL_UART_Receive_IT(&huart2, buffer, 1);
        case SerialPort::BLUETOOTH:
            MX_USART2_UART_Init();
            HAL_UART_Receive_IT(&huart1, buffer, 1);
            break;
        default:
            break;
    }
}

void SerialController::end() {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_MspDeInit(&huart2);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_MspDeInit(&huart1);
            break;
        default:
            break;
    }
}

void SerialController::write(const char data) {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_Transmit(&huart2, (uint8_t*)&data, 1, TIMEOUT_MS);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_Transmit(&huart1, (uint8_t*)&data, 1, TIMEOUT_MS);
            break;
        default:
            break;
    }
}

void SerialController::write(const uint8_t data) {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_Transmit(&huart2, (uint8_t*)&data, 1, TIMEOUT_MS);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_Transmit(&huart1, (uint8_t*)&data, 1, TIMEOUT_MS);
            break;
        default:
            break;
    }
}

void SerialController::write(const char* data) {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), TIMEOUT_MS);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen(data), TIMEOUT_MS);
            break;
        default:
            break;
    }
}
void SerialController::write(const uint8_t* data) {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen((char*)data), TIMEOUT_MS);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen((char*)data), TIMEOUT_MS);
            break;
        default:
            break;
    }
}
void SerialController::write(const char* data, const uint32_t length) {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_Transmit(&huart2, (uint8_t*)data, length, TIMEOUT_MS);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_Transmit(&huart1, (uint8_t*)data, length, TIMEOUT_MS);
            break;
        default:
            break;
    }
}

void SerialController::write(const uint8_t* data, const uint32_t length) {
    switch (serial_num) {
        case SerialPort::UART:
            HAL_UART_Transmit(&huart2, (uint8_t*)data, length, TIMEOUT_MS);
            break;
        case SerialPort::BLUETOOTH:
            HAL_UART_Transmit(&huart1, (uint8_t*)data, length, TIMEOUT_MS);
            break;
        default:
            break;
    }
}

void SerialController::read(uint8_t* data, const uint32_t length) {
    uint8_t tmp = 0;
    for (uint32_t i = 0; i < length; i++) {
        if (ring_buffer_dequeue(&ring_buffer, (char*)&tmp) > 0) {
            data[i] = tmp;
        }
        break;
    }
}

bool SerialController::available() {
    return !ring_buffer_is_empty(&ring_buffer);
}