#include "button.h"

bool Button::read()
{
    if (this->active)
    {
        this->active = false;
        return true;
    }
    else
    {
        return false;
    }
}

void Button::start()
{
    this->buttonPin->mode(PullUp);
    this->buttonPin->attach_deasserted(this, &Button::pressed_callback);
    this->buttonPin->setSampleFrequency();
}

void Button::pressed_callback()
{
    this->active = true;
}
