#include "outlet.h"

bool Outlet::set(bool active)
{
    this->active = active;
    if (this->active && this->enabled)
        *this->pin = 1;
    else if (!this->active)
        *this->pin = 0;
    return this->active;
}

void Outlet::enable(bool enable)
{
    this->enabled = enable;
    if (!this->enabled)
        this->set(false);
}
