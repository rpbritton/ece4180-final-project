#include "speakerOut.h"

char *SpeakerOut::name = "Speaker";

void SpeakerOut::enable(bool enable)
{
    this->enabled = enable;
}

void SpeakerOut::set(bool active)
{
    if (this->enabled)
    {
        this->speaker->period(1.0 / this->note);
        *this->speaker = 0.5;
        wait(this->duration);
        *this->speaker = 0.0;
    }
}
