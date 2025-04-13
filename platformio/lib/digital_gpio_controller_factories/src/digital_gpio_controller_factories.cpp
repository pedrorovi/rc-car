#include "digital_gpio_controller_factories.h"

#include "digital_gpio_controller.h"
#include "app.h"

DigitalGpioController* green_led = nullptr;
DigitalGpioController* red_led = nullptr;
DigitalGpioController* motor_enable = nullptr;

DigitalGpioInterface* getLedGreenFactory() {
    if (green_led == nullptr) {
        PinPort pin = {Port::B, LED_GREEN_Pin};
        green_led = new DigitalGpioController(pin);
        green_led->setup();
    }
    return green_led;
}

DigitalGpioInterface* getLedRedFactory() {
    if (red_led == nullptr) {
        PinPort pin = {Port::B, LED_RED_Pin};
        red_led = new DigitalGpioController(pin);
        red_led->setup();
    }
    return red_led;
}

DigitalGpioInterface* getMotorEnableFactory() {
    if (motor_enable == nullptr) {
        PinPort pin = {Port::B, MOTOR_EN_Pin};
        motor_enable = new DigitalGpioController(pin);
        motor_enable->setup();
    }
    return motor_enable;
}
