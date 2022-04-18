#pragma once

class Output
{
public:
    void set(bool active);
    void enable(bool enable);
    virtual char *description() = 0;
};
