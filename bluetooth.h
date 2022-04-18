#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Bluetooth : public Activator
{
private:
    static char *name;

    Serial *serial;

    Thread thread;
    void thread_func();

    Mutex lock;
    ActivatorState state;

public:
    Bluetooth(Serial *serial) : serial(serial), state(ACTIVATOR_INACTIVE) {}
    bool read();
    void enable(bool enable);
    void start();
    virtual char *description() { return this->name; }
};
