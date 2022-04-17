#pragma once

#include "mbed.h"
#include "output.h"
#include "Servo.h"
class ServoOut : Output
{
private:
    Servo *servo;

    bool enabled;
    
    bool currentVal;

public:
    ServoOut(Servo *servo) : servo(servo), enabled(true), currentVal(false) {}
    void enable(bool enable);
    bool set(bool active);
};