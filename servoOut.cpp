#include "servoOut.h"
void ServoOut::enable(bool enable)
{
    this->enabled = enable;
}

bool ServoOut::set(bool active)
{
    if(this->enabled)
    {
        //if light is on, turn it off
        if(currentVal)
        {
            *(this->servo) = 1.0; 
            currentVal = false;
        }
        //if light is off, turn it on
        else
        {
            *(this->servo) = 0.0;
            currentVal = true;
        }
    }
    return true;
}
