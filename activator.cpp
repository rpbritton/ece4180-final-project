#include "activator.h"

bool Activator::state()
{
    if (!this->enabled)
        return false;
    
    return this->read();
}

void Activator::enable(bool enabled)
{
    // clear stale read
    if (!this->enabled && enabled)
        this->read();

    this->enabled = enabled;
}
