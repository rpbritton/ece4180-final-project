#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Bluetooth : public Activator
{
private:
    Serial *serial;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;
    Mutex lock;
    ActivatorState state;

    static char *name;

public:
    Bluetooth(Serial *serial) : serial(serial), active(false) {}
    Bluetooth(Serial *serial) : serial(serial), state(ACTIVATOR_INACTIVE) {}
    bool read();
    void enable(bool enable);
    void start();
    virtual char *description() { return this->name; }
};
