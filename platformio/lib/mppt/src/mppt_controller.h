#pragma once

#include "mppt_interface.h"

class MPPT : public MpptInterface {
   public:
    MPPT(const uint16_t pwm_min, const uint16_t pwm_max, const uint16_t pwm_step);

    uint16_t update(const float voltage_v, const float current_amp) override;

   private:
    void updatePwm(const bool power_is_higher_than_last, const bool voltage_is_higher_than_last);
    void calcPwm(const MpptData_t& pv, const MpptData_t& last_pv);

    MpptData_t pv;
    MpptData_t last_pv;
    PwmData_t pwm;
};