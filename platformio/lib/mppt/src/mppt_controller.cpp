#include "mppt_controller.h"

MPPT::MPPT(const uint16_t pwm_min, const uint16_t pwm_max, const uint16_t pwm_step) {
    pwm(pwm_min, pwm_max, pwm_step);
}

uint16_t MPPT::update(const float voltage_v, const float current_amp) {
    pv(voltage_v, current_amp);
    calcPwm(pv, last_pv);
    last_pv = pv;
    return pwm.val;
}

void MPPT::updatePwm(const bool power_is_higher_than_last, const bool voltage_is_higher_than_last) {
    if (power_is_higher_than_last) {
        voltage_is_higher_than_last ? pwm.increase() : pwm.decrease();
    } else {
        voltage_is_higher_than_last ? pwm.decrease() : pwm.increase();
    }
}

void MPPT::calcPwm(const MpptData_t& pv, const MpptData_t& last_pv) {
    const bool power_is_higher_than_last = pv.power_watt > last_pv.power_watt;
    const bool voltage_is_higher_than_last = pv.voltage_v > last_pv.voltage_v;
    updatePwm(power_is_higher_than_last, voltage_is_higher_than_last);
}
