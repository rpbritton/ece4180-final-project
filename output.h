#pragma once

class Output
{
public:
    virtual void set(bool active) = 0;
    virtual void enable(bool enable) = 0;
    virtual char *description() = 0;
};
