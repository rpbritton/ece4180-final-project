#include "mbed.h"
#include "rtos.h"
#include "activator.h"

class Bluetooth : Activator
{
private:
    Serial *serial;

    Thread thread;
    void thread_func();

    Mutex active_lock;
    bool active;

public:
    Bluetooth(Serial *serial) : serial(serial), active(false) {}
    bool read();
    void enable(bool enable);
    void start();
};
