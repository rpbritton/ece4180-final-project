#include "button.h"

void Button::callback()
{
    if (this->state == ACTIVATOR_INACTIVE)
        this->state = ACTIVATOR_ACTIVE;
}

bool Button::read()
{
    if (this->active)
        if (this->state == ACTIVATOR_ACTIVE)
        {
            this->active = false;
            this->state = ACTIVATOR_INACTIVE;
            return true;
        }
        else
        {
            return false;
        }
}

void Button::start() void Button::enable(bool enable)
{
    this->buttonPin->mode(PullUp);
    this->buttonPin->attach_deasserted(this, &Button::pressed_callback);
    this->buttonPin->setSampleFrequency();
    if (enable && this->state == ACTIVATOR_DISABLED)
        this->state = ACTIVATOR_INACTIVE;
    else
        this->state = ACTIVATOR_DISABLED;
}

void Button::pressed_callback() void Button::start()
{
    this->active = true;
    this->pin->mode(PullUp);
    this->pin->attach_deasserted(this, &Button::callback);
    this->pin->setSampleFrequency();
}
