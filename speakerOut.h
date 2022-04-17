#pragma once

#include "mbed.h"
#include "output.h"
class SpeakerOut : Output
{
private:
    PwmOut *speaker;

    float note;
    float duration;

    bool enabled;

public:
    SpeakerOut(PwmOut *speaker, float note, float duration) : speaker(speaker), enabled(true), note(note), duration(duration) {}
    void enable(bool enable);
    bool set(bool active);
};