#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Photoresistor : public Activator
{
private:
    AnalogIn *sensor;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;

    bool prevReading;

    bool enabled;

    static char *name;

public:
    Photoresistor(AnalogIn *sensor) : sensor(sensor), active(false), prevReading(false) {}
    bool read();
    void enable(bool enable);
    void start();
    virtual char *description() { return this->name; }
};
