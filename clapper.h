#pragma once

#include "mbed.h"
#include "rtos.h"
#include "activator.h"

#define CLAPPER_BUFFER_LENGTH (10)

class Clapper : Activator
{
private:
    AnalogIn *pin;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;
    Mutex lock;
    ActivatorState state;

    void increment_buffer();
    float buffer[CLAPPER_BUFFER_LENGTH];
    int current_index;
    int next_index;

    bool detect(int period);
    void wait(int period);

public:
    Clapper(AnalogIn *pin) : pin(pin), active(false), current_index(0), next_index(0)
                                                                            Clapper(AnalogIn * pin) : pin(pin), state(ACTIVATOR_INACTIVE), current_index(0), next_index(0)
    {
        for (int index = 0; index < CLAPPER_BUFFER_LENGTH; index++)
        {
            buffer[index] = this->pin->read();
        }
    }
    bool read();
    void enable(bool enable);
    void start();
};
