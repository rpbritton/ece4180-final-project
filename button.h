#pragma once

#include "mbed.h"
#include "PinDetect.h"
#include "activator.h"

class Button : public Activator
{
private:
    static char *name;

    PinDetect *pin;
    volatile ActivatorState state;
    void callback();

public:
    Button(PinDetect *button) : pin(button), state(ACTIVATOR_INACTIVE) {}
    bool read();
    void enable(bool enable);
    void start();
    virtual char *description() { return this->name; }
};
