#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Sonar : public Activator
{
private:
    DigitalOut *trigger;
    DigitalIn *echo;

    Timer *sonar;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;

    bool enabled;

    bool prevReading;

    int correction;

    static char *name;

public:
    Sonar(DigitalOut *trigger, DigitalIn *echo, Timer *sonar) : trigger(trigger), echo(echo), sonar(sonar), active(false), prevReading(false) {}
    bool read();
    void enable(bool enable);
    void start();
    virtual char *description() { return this->name; }
};
