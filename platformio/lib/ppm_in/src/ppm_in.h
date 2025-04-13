#pragma once

#include "ppm_in_interface.h"

class PPMIn : public PPMInInterface {
   public:
    PPMIn(const uint8_t chnl) : chnl(chnl) {
        pulseWidthUs = 0;
        pulseWidthTicks = 0;
        diff = 0;
        isFirstCapture = true;
        freq = 0;
        riseCapture = 0;
        fallCapture = 0;
    }
    bool start() override;
    void stop() override;
    float getPulseWidthUs() override;
    void updatePulseWidth() override;

   private:
    const uint8_t chnl;
    float pulseWidthUs;
    uint32_t pulseWidthTicks;
    uint32_t diff;
    bool isFirstCapture;
    float freq;
    uint32_t riseCapture;
    uint32_t fallCapture;
};