#include "button.h"

char *Button::name = "Button";

void Button::callback()
{
    this->activated = true;
}

bool Button::read()
{
    bool activated = this->activated;
    this->activated = false;
    return activated;
}

void Button::start()
{
    this->pin.mode(PullUp);
    this->pin.attach_deasserted(this, &Button::callback);
    this->pin.setSampleFrequency();
}
