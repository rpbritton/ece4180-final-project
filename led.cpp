#include "led.h"

char *Led::name = "LED";

void Led::set(bool state)
{
    if (state)
        this->pin = 1;
    else
        this->pin = 0;
}
