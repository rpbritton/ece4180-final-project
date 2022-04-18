#pragma once

class Activator
{
private:
    bool enabled;
    
protected:
    virtual bool read() = 0;

public:
    Activator() : enabled(false) {};
    virtual void start() = 0;
    bool state();
    void enable(bool enabled);
    virtual char *description() = 0;
};
