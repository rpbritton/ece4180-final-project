#pragma once

#include "mbed.h"
#include "PinDetect.h"
#include "activator.h"

class Button : public Activator
{
private:
    static char *name;

    PinDetect pin;
    volatile bool activated;
    void callback();

protected:
    virtual bool read();

public:
    Button(PinName pin) : pin(pin), activated(false) {}
    virtual void start();
    virtual char *description() { return this->name; }
};
