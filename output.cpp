#include "output.h"

void Output::activate(bool activated)
{
    if (this->enabled)
    {
        this->activated = activated;
        this->set(this->activated);
    }
}

void Output::enable(bool enabled)
{
    this->enabled = enabled;
    if (!this->enabled)
    {
        this->activated = false;
        this->set(false);
    }
}
