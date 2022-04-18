#include "speakerOut.h"

char *SpeakerOut::name = "Speaker";

void SpeakerOut::set(bool state)
{
    // TODO: add different noise if on or off
    this->speaker->period(1.0 / this->note);
    *this->speaker = 0.5;
    wait(this->duration);
    *this->speaker = 0.0;
}
