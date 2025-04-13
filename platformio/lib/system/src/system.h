#pragma once

#include "stdint.h"

#include "INA219_interface.h"
#include "debug.h"
#include "digital_gpio_interface.h"
#include "motor_interface.h"
#include "mppt_interface.h"
#include "ppm_in_interface.h"
#include "pwm_interface.h"
#include "stepper_interface.h"
#include "watchdog_interface.h"

class System {
   public:
    System(DigitalGpioInterface* led_red,
           DigitalGpioInterface* led_green,
           MotorInterface* motor,
           StepperInterface* stepper,
           PPMInInterface* motor_ppm_in,
           PPMInInterface* stepper_ppm_in,
           WatchdogInterface* watchdog,
           INA219_interface* ina219,
           MpptInterface* mppt,
           Debug* debug)
        : _led_red(led_red),
          _led_green(led_green),
          _motor(motor),
          _stepper(stepper),
          _motor_ppm_in(motor_ppm_in),
          _stepper_ppm_in(stepper_ppm_in),
          _watchdog(watchdog),
          _ina219(ina219),
          _mppt(mppt),
          _debug(debug) {}

    DigitalGpioInterface* getLedRed() { return _led_red; }
    DigitalGpioInterface* getLedGreen() { return _led_green; }
    MotorInterface* getMotor() { return _motor; }
    StepperInterface* getStepper() { return _stepper; }
    PPMInInterface* getMotorPPMIn() { return _motor_ppm_in; }
    PPMInInterface* getStepperPPMIn() { return _stepper_ppm_in; }
    WatchdogInterface* getWatchdog() { return _watchdog; }
    INA219_interface* getINA219() { return _ina219; }
    MpptInterface* getMppt() { return _mppt; }
    Debug* getDebug() { return _debug; }

   private:
    DigitalGpioInterface* _led_red;
    DigitalGpioInterface* _led_green;
    MotorInterface* _motor;
    StepperInterface* _stepper;
    PPMInInterface* _motor_ppm_in;
    PPMInInterface* _stepper_ppm_in;
    WatchdogInterface* _watchdog;
    INA219_interface* _ina219;
    MpptInterface* _mppt;
    Debug* _debug;
};