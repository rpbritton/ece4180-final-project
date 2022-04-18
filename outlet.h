#pragma once

#include "mbed.h"
#include "output.h"

#define CLAPPER_BUFFER_LENGTH (10)

class Outlet : Output
{
private:
    DigitalOut *pin;
    bool enabled;
    bool active;

public:
    Outlet(DigitalOut *pin) : pin(pin), active(false), enabled(true) {}
    bool set(bool active);
    void enable(bool enable);
};
