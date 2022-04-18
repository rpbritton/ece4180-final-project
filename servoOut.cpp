#include "servoOut.h"

char *ServoOut::name = "Servo";

void ServoOut::set(bool state)
{
    if (state)
        *this->servo = 0;
    else
        *this->servo = 1;
}
