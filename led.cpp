#include "led.h"

char *Led::name = "LED";

void Led::set(bool active)
{
    this->active = active;
    if (this->enabled)
    {
        if (this->active)
            *this->pin = 1;
        else
            *this->pin = 0;
    }
}

void Led::enable(bool enable)
{
    // deactivate if disabled
    if (!enable && this->active)
    {
        this->set(false);
        this->active = true;
    }
    this->enabled = enable;
}
