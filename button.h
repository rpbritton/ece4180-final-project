#pragma once

#include "mbed.h"
#include "PinDetect.h"
#include "activator.h"

class Button : Activator
{
private:
    PinDetect *buttonPin;
    volatile bool active;
    void pressed_callback();

public:
    Button(PinDetect *button) : buttonPin(button), active(false) {}
    bool read();
    void enable(bool enable);
    void start();
};
