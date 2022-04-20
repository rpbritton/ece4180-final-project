#pragma once

#include "mbed.h"
#include "output.h"

class SpeakerOut : public Output
{
private:
    static char *name;

    PwmOut speaker;

    float note;
    float duration;

protected:
    virtual void set(bool state);

public:
    SpeakerOut(PinName pin, float note, float duration) : speaker(pin), note(note), duration(duration) {}
    virtual char *description() { return this->name; }
};
