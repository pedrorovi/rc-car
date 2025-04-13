#pragma once

#include "watchdog_interface.h"

class WatchdogController : public WatchdogInterface {
   public:
    WatchdogController() {}
    ~WatchdogController() override {}

    void setup() override;
    void refresh() override;

   private:
};