#pragma once

#include "mbed.h"
#include "output.h"

#define CLAPPER_BUFFER_LENGTH (10)

class Outlet : public Output
{
private:
    static char *name;

    DigitalOut *pin;
    bool enabled;
    bool active;

public:
    Outlet(DigitalOut *pin) : pin(pin), enabled(true), active(true) {}
    void set(bool active);
    void enable(bool enable);
    virtual char *description() { return this->name; }
};
