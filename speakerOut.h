#pragma once

#include "mbed.h"
#include "output.h"

class SpeakerOut : public Output
{
private:
    static char *name;

    PwmOut *speaker;

    float note;
    float duration;

    bool enabled;

public:
    SpeakerOut(PwmOut *speaker, float note, float duration) : speaker(speaker), note(note), duration(duration), enabled(true) {}
    void enable(bool enable);
    void set(bool active);
    virtual char *description() { return this->name; }
};
