#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Photoresistor : public Activator
{
private:
    static char *name;

    AnalogIn *sensor;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;

    bool prevReading;

    bool enabled;

public:
    Photoresistor(AnalogIn *sensor) : sensor(sensor), active(false), prevReading(false) {}
    virtual bool read();
    virtual void enable(bool enable);
    virtual void start();
    virtual char *description() { return this->name; }
};
