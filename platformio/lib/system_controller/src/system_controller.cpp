#include "system_controller.h"

bool setupSystem(System* system) {
    Debug* debug = system->getDebug();

    system->getLedGreen()->setup();
    system->getLedRed()->setup();
    if (!system->getStepper()->setup()) {
        debug->error("Failed to setup stepper");
        return false;
    }
    if (!system->getMotor()->setup()) {
        debug->error("Failed to setup motor");
        return false;
    }
    if (!system->getMotorPPMIn()->start()) {
        debug->error("Failed to start motor PPM input");
        return false;
    }
    if (!system->getStepperPPMIn()->start()) {
        debug->error("Failed to start stepper PPM input");
        return false;
    }
    // system->getWatchdog()->setup();

    system->getINA219()->setCalibration_32V_1A();

    debug->info("System setup complete");

    return true;
}

static float map(const float x,
                 const float in_min = 1000,
                 const float in_max = 2000,
                 const float out_min = -100,
                 const float out_max = 100) {
    return (x - in_min) * ((out_max - out_min) / (in_max - in_min)) + out_min;
}

bool mpptLoop(System* system) {
    Debug* debug = system->getDebug();
    MotorInterface* motor = system->getMotor();
    PPMInInterface* motorPPMIn = system->getMotorPPMIn();
    INA219_interface* ina = system->getINA219();
    MpptInterface* mppt = system->getMppt();

    const float shuntVoltage_mV = ina->getShuntVoltage_mV();
    const float busVoltage = ina->getBusVoltage_V();
    const float power = ina->getPower_mW();
    const float current_mA = ina->getCurrent_mA();
    debug->debug("Shunt voltage: %.2f mV, Bus voltage: %.2f V, Power: %.2f mW, Current: %.2f mA", shuntVoltage_mV,
                 busVoltage, power, current_mA);

    const uint32_t motorPulseWidth = motorPPMIn->getPulseWidthUs();
    debug->trace("Motor PPM pulse width: %u us", motorPulseWidth);
    // motor->setSpeed(map(motorPulseWidth));

    const uint16_t mppt_val = mppt->update(busVoltage + (shuntVoltage_mV / 1000), current_mA);
    debug->trace("MPPT value: %u", mppt_val);

    float mppt_float = float(mppt_val) / 100.0;
    debug->debug("MPPT float value: %.2f", mppt_float);
    float mapped_us = float(map(motorPulseWidth));
    debug->trace("Mapped us: %.2f", mapped_us);

    float val = (float)motorPulseWidth + ((float)motorPulseWidth - 1500.0f) * mppt_float;
    debug->trace("Motor pulse width: %u, MPPT float: %.2f, Value: %.2f", motorPulseWidth, mppt_float, val);

    float new_speed = map(val);
    debug->debug("New speed: %d - %.2f", motorPulseWidth, new_speed);

    if (new_speed > 100) {
        new_speed = 100;
    } else if (new_speed < -100) {
        new_speed = -100;
    }
    motor->setSpeed((int16_t)new_speed);

    return true;
}

void updateStepperLoop(System* system) {
    Debug* debug = system->getDebug();
    StepperInterface* stepper = system->getStepper();
    PPMInInterface* stepperPPMIn = system->getStepperPPMIn();
    const uint32_t stepperPulseWidth = stepperPPMIn->getPulseWidthUs();
    // debug->trace("Stepper PPM pulse width: %u us", stepperPulseWidth);
    stepper->setDirection(stepperPulseWidth);
}
