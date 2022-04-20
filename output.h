#pragma once

class Output
{
private:
    bool activated, enabled;

protected:
    virtual void set(bool state) = 0;

public:
    Output() : activated(false), enabled(false){};
    bool activate(bool activated);
    void enable(bool enabled);
    virtual char *description() = 0;
};
