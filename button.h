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
    PinDetect *pin;
    volatile ActivatorState state;
    void callback();

public:
    Button(PinDetect *button) : buttonPin(button), active(false) {}
    Button(PinDetect *button) : pin(button), state(ACTIVATOR_INACTIVE) {}
    bool read();
    void enable(bool enable);
    void start();
};
