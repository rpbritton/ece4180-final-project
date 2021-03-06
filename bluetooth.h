#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Bluetooth : public Activator
{
private:
    static char *name;

    Serial serial;

    Thread thread;
    void thread_func();

    Mutex lock;
    bool activated;

protected:
    virtual bool read();

public:
    Bluetooth(PinName tx, PinName rx) : serial(tx, rx), activated(false) {}
    virtual void start();
    virtual char *description() { return this->name; }
};
