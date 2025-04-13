#include "motor_controller_factory.h"

#include "digital_gpio_controller_factories.h"
#include "motor_controller.h"
#include "pwm_hal.h"

static const uint8_t PWM_CHANNEL = 1;
static const float DT_SECONDS = 0.1;
static const float MAX_SPEED = 500;
static const float MIN_SPEED = -500;
static const float KP = 0.6;
static const float KD = 0.001;
static const float KI = 0.05;

static PwmHal* pwm = nullptr;
static PID* pid = nullptr;
static DigitalGpioInterface* enable = nullptr;

static MotorController* motor = nullptr;

MotorInterface* getMotorInterfaceFactory() {
    if (motor == nullptr) {
        pwm = new PwmHal(PWM_CHANNEL);
        enable = getMotorEnableFactory();
        pid = new PID(DT_SECONDS, MAX_SPEED, MIN_SPEED, KP, KD, KI);
        motor = new MotorController(pwm, enable, pid);
    }
    return motor;
}
