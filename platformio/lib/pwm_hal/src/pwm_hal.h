#pragma once

#include "pwm_interface.h"

class PwmHal : public PWMInterface {
   public:
    PwmHal(const uint8_t chnl);
    ~PwmHal() {}

    bool start() override;
    void stop() override;
    void updateDuty(const uint32_t duty) override;
    uint32_t getDuty() override;

   private:
    uint8_t chnl;
    uint32_t duty;
    uint32_t frequency;
};