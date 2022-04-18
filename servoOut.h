#pragma once

#include "mbed.h"
#include "output.h"
#include "Servo.h"

class ServoOut : public Output
{
private:
    static char *name;

    Servo *servo;
    bool enabled;
    bool active;

public:
    ServoOut(Servo *servo) : servo(servo), enabled(true), active(false) {}
    virtual void enable(bool enable);
    virtual void set(bool active);
    virtual char *description() { return this->name; }
};
