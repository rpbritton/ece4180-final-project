#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Photoresistor : Activator
{
private:
    AnalogIn *sensor;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;

    bool prevReading;

    bool enabled;

public:
    Photoresistor(AnalogIn *sensor) : sensor(sensor), active(false), prevReading(false) {}
    bool read();
    void enable(bool enable);
    void start();
};