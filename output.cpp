#include "output.h"

bool Output::activate(bool activated)
{
    if (!this->enabled)
        return false;
    
    this->activated = activated;
    this->set(this->activated);
    return true;
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
