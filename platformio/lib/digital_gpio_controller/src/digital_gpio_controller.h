#pragma once

#include "digital_gpio_interface.h"

class DigitalGpioController : public DigitalGpioInterface {
   public:
    DigitalGpioController(PinPort pin) : pin_(pin) {}

    void setup() override;
    void digitalWrite(int value) override;
    int digitalRead() override;
    void toggle() override;

   private:
    PinPort pin_;
};