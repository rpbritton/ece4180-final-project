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
    bool read();
    void enable(bool enable);
    void start();
};
