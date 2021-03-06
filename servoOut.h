#pragma once

#include "mbed.h"
#include "output.h"
#include "Servo.h"

class ServoOut : public Output
{
private:
    static char *name;

    Servo servo;
    
protected:
    virtual void set(bool state);

public:
    ServoOut(PinName pin) : servo(pin) {}
    virtual char *description() { return this->name; }
};
