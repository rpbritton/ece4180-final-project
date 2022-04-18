#pragma once

typedef enum
{
    ACTIVATOR_DISABLED,
    ACTIVATOR_INACTIVE,
    ACTIVATOR_ACTIVE
} ActivatorState;

class Activator
{
public:
    virtual bool read() = 0;
    virtual void enable(bool enable) = 0;
    virtual void start() = 0;
    virtual char *description() = 0;
};
