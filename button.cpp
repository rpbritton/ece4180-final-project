#include "button.h"

char *Button::name = "Button";

void Button::callback()
{
    if (this->state == ACTIVATOR_INACTIVE)
        this->state = ACTIVATOR_ACTIVE;
}

bool Button::read()
{
    if (this->state == ACTIVATOR_ACTIVE)
    {
        this->state = ACTIVATOR_INACTIVE;
        return true;
    }
    else
    {
        return false;
    }
}

void Button::enable(bool enable)
{
    if (enable && this->state == ACTIVATOR_DISABLED)
        this->state = ACTIVATOR_INACTIVE;
    else
        this->state = ACTIVATOR_DISABLED;
}

void Button::start()
{
    this->pin->mode(PullUp);
    this->pin->attach_deasserted(this, &Button::callback);
    this->pin->setSampleFrequency();
}
