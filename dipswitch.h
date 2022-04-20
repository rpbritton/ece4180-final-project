#pragma once

#include "mbed.h"
#include "PinDetect.h"

class Dipswitch
{
private:
    PinDetect pin;
    volatile bool change;
    void callback();

public:
    Dipswitch(PinName pin) : pin(pin), change(true) {};
    void start();
    bool changed();
    bool read();
};