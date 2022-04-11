#include "clapper.h"

#define CLAPPER_THRESHOLD (0.005)

void Clapper::increment_buffer()
{
    Thread::wait(1);
    this->current_index = this->next_index;
    this->next_index = (this->current_index + 1) % CLAPPER_BUFFER_LENGTH;
    this->buffer[this->current_index] = this->pin->read();
}

bool Clapper::detect(int period)
{
    for (int count = 0; count < period; count++)
    {
        this->increment_buffer();
        if (this->buffer[this->current_index] * (1 - CLAPPER_THRESHOLD) > this->buffer[this->next_index])
        {
            return true;
        }
    }
    return false;
}

void Clapper::wait(int period)
{
    for (int count = 0; count < 50; count++)
        this->increment_buffer();
}

void Clapper::thread_func()
{
    while (1)
    {
        if (!this->detect(250))
            continue;

        this->wait(50);

        if (!this->detect(250))
            continue;

        this->active_lock.lock();
        this->active = true;
        this->active_lock.unlock();

        this->wait(50);
    }
}

bool Clapper::read()
{
    this->active_lock.lock();
    bool active = this->active;
    this->active = false;
    this->active_lock.unlock();
    return active;
}

void Clapper::start()
{
    this->thread.start(callback(this, &Clapper::thread_func));
}
