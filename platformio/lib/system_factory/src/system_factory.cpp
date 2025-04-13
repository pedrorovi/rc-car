#include "system_factory.h"

#include "debug_factory.h"
#include "digital_gpio_controller_factories.h"
#include "ina219_factory.h"
#include "motor_controller_factory.h"
#include "mppt_controller.h"
#include "ppm_in_factory.h"
#include "servo_controller_factory.h"
#include "watchdog_controller.h"

System* system = nullptr;
static MpptInterface* mppt = nullptr;

WatchdogInterface* watchdog = nullptr;

System* getSystem() {
    if (system == nullptr) {
        watchdog = new WatchdogController();
        mppt = new MPPT(20, 80, 1);
        system = new System(getLedRedFactory(), getLedGreenFactory(), getMotorInterfaceFactory(),
                            getServoInterfaceFactory(), getMotorPPMInInterface(), getServoPPMInInterface(),
                            watchdog, getINA219Interface(), mppt, getDebugFactory());
    }
    return system;
}
