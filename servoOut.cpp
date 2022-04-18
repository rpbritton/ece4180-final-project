#include "servoOut.h"

char *ServoOut::name = "Servo";

void ServoOut::enable(bool enable)
{
    // deactivate if disabled
    if (!enable && this->active)
    {
        this->set(false);
        this->active = true;
    }
    this->enabled = enable;
}

void ServoOut::set(bool active)
{
    this->active = active;
    if (this->enabled)
    {
        if (this->active)
            *this->servo = 0;
        else
            *this->servo = 1;
    }
}
