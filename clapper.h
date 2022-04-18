#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

#define CLAPPER_BUFFER_LENGTH (10)

class Clapper : public Activator
{
private:
    static char *name;

    AnalogIn *pin;

    Thread thread;
    void thread_func();

    Mutex lock;
    bool activated;

    void increment_buffer();
    float buffer[CLAPPER_BUFFER_LENGTH];
    int current_index;
    int next_index;

    bool detect(int period);
    void wait(int period);
    
protected:
    virtual bool read();

public:
    Clapper(AnalogIn *pin) : pin(pin), activated(false), current_index(0), next_index(0) {}
    virtual void start();
    virtual char *description() { return this->name; }
};
