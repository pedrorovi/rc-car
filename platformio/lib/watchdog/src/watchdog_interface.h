#pragma once

struct WatchdogInterface {
    virtual void setup() = 0;
    virtual void refresh() = 0;

    virtual ~WatchdogInterface() = default;
};