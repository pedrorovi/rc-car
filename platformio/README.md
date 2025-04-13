# RC Solar Car - STM32L432KC

This project is an embedded software application for controlling an RC solar-powered car using the STM32L432KC microcontroller. It includes various modules for hardware abstraction, motor control, power monitoring, and communication.

## Project Structure

. ├── .clang-format # Code formatting configuration ├── .gitignore # Git ignore rules ├── Makefile # Build system configuration ├── platformio.ini # PlatformIO project configuration ├── include/ # Header files for the project ├── lib/ # Libraries for hardware abstraction and drivers │ ├── FreeRTOS/ # FreeRTOS kernel source │ ├── hal/ # Hardware Abstraction Layer │ ├── motor_controller/ # Motor control logic │ ├── ina219/ # INA219 power sensor driver │ ├── debug/ # Debugging utilities │ └── ... # Other libraries ├── src/ # Application source code │ └── main.cpp # Main application entry point ├── test/ # Unit tests for the project └── README.md # Project documentation

## Features

- **Motor Control**: Includes modules for controlling DC and servo motors.
- **Power Monitoring**: Uses the INA219 sensor to measure current and voltage.
- **FreeRTOS Integration**: Real-time operating system for task scheduling.
- **Debugging Utilities**: Provides logging and debugging support.
- **Hardware Abstraction**: Simplifies interaction with peripherals like GPIO, I2C, and UART.

## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) installed on your system.
- STM32L432KC microcontroller development board.
- INA219 power sensor module.
- Motor drivers and motors.

### Building the Project

1. Build the project using PlatformIO:

```bash
make build_embedded
```

Upload the firmware to the STM32L432KC board:

```bash
make flash_embedded
```

Running Unit Tests
To run unit tests, use the PlatformIO Test Runner:

```bash
make test_*
```

License
This project includes components licensed under various open-source licenses:

The STM32 HAL driver is licensed under the BSD 3-Clause License.
The CMSIS library is licensed under the Apache License 2.0.
FreeRTOS is licensed under the MIT License.
Refer to the respective License.md files in the project for more details.

Contributing
Contributions are welcome! Please follow the coding style defined in the .clang-format file and ensure all tests pass before submitting a pull request.

Acknowledgments
STMicroelectronics for the STM32 HAL and CMSIS libraries.
Adafruit for the INA219 driver.
PlatformIO for the development environment.
For more information, refer to the documentation in the source code and the PlatformIO documentation. ```
