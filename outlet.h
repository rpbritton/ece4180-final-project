#pragma once

#include "mbed.h"
#include "output.h"

class Outlet : public Output
{
private:
    static char *name;

    DigitalOut pin;
    
protected:
    virtual void set(bool active);

public:
    Outlet(PinName pin) : pin(pin) {}
    virtual char *description() { return this->name; }
};
