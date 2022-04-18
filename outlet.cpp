#include "outlet.h"

char *Outlet::name = "Outlet";

void Outlet::set(bool active)
{
    this->active = active;
    if (this->enabled)
    {
        if (this->active)
            *this->pin = 1;
        else
            *this->pin = 0;
    }
}

void Outlet::enable(bool enable)
{
    // deactivate if disabled
    if (!enable && this->active)
    {
        this->set(false);
        this->active = true;
    }
    this->enabled = enable;
}
