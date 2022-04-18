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
    virtual bool read();
    virtual void enable(bool enable);
    virtual void start();
    virtual char *description() { return this->name; }
};
