#include "dipswitch.h"

void Dipswitch::callback()
{
    this->change = true;
}

void Dipswitch::start()
{
    this->pin.mode(PullUp);
    this->pin.attach_asserted(this, &Dipswitch::callback);
    this->pin.attach_deasserted(this, &Dipswitch::callback);
    this->pin.setSampleFrequency();
}

bool Dipswitch::changed()
{
    bool change = this->change;
    this->change = false;
    return change;
}

bool Dipswitch::read()
{
    return this->pin == 1;
}