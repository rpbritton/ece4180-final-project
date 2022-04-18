#pragma once

#include "mbed.h"
#include "output.h"

class Led : public Output
{
private:
    static char *name;

    DigitalOut *pin;
    bool enabled;
    bool active;

public:
    Led(DigitalOut *pin) : pin(pin), enabled(true), active(true) {}
    virtual void set(bool active);
    virtual void enable(bool enable);
    virtual char *description() { return this->name; }
};
