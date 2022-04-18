#include "outlet.h"

char *Outlet::name = "Outlet";

void Outlet::set(bool state)
{
    if (state)
        *this->pin = 1;
    else
        *this->pin = 0;
}