#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Sonar : public Activator
{
private:
    static char *name;

    DigitalOut *trigger;
    DigitalIn *echo;

    Timer *sonar;

    Thread thread;
    void thread_func();

    Mutex lock;
    bool activated;

    bool prevReading;

    int correction;
    
protected:
    virtual bool read();

public:
    Sonar(DigitalOut *trigger, DigitalIn *echo, Timer *sonar) : trigger(trigger), echo(echo), sonar(sonar), activated(false), prevReading(false) {}
    virtual void start();
    virtual char *description() { return this->name; }
};
