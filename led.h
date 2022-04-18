#pragma once

#include "mbed.h"
#include "output.h"

class Led : public Output
{
private:
    static char *name;

    DigitalOut *pin;
    
protected:
    virtual void set(bool active);

public:
    Led(DigitalOut *pin) : pin(pin) {}
    virtual char *description() { return this->name; }
};
