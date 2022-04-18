#pragma once

class Output
{
public:
    bool set(bool active);
    void enable(bool enable);
    virtual char *description() = 0;
};
