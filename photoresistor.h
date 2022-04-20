#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Photoresistor : public Activator
{
private:
    static char *name;

    AnalogIn sensor;

    Thread thread;
    void thread_func();

    Mutex lock;
    bool activated;

    bool prevReading;

protected:
    virtual bool read();

public:
    Photoresistor(PinName pin) : sensor(pin), activated(false), prevReading(false) {}
    virtual void start();
    virtual char *description() { return this->name; }
};
