#pragma once

#include "mbed.h"
#include "output.h"

class Outlet : public Output
{
private:
    static char *name;

    DigitalOut *pin;
    bool enabled;
    bool active;

public:
    Outlet(DigitalOut *pin) : pin(pin), enabled(true), active(true) {}
    virtual void set(bool active);
    virtual void enable(bool enable);
    virtual char *description() { return this->name; }
};
