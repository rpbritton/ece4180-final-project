#include "clapper.h"

char *Clapper::name = "Clapper";

void Clapper::increment_buffer()
{
    Thread::wait(1);
    this->current_index = this->next_index;
    this->next_index = (this->current_index + 1) % CLAPPER_BUFFER_LENGTH;
    this->buffer[this->current_index] = this->pin.read();
}

bool Clapper::detect(int period)
{
    for (int count = 0; count < period; count++)
    {
        this->increment_buffer();
        if (this->buffer[this->current_index] * (1 - this->threshold) > this->buffer[this->next_index])
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

        this->lock.lock();
        this->activated = true;
        this->lock.unlock();

        this->wait(50);
    }
}

bool Clapper::read()
{
    this->lock.lock();
    bool activated = this->activated;
    this->activated = false;
    this->lock.unlock();
    return activated;
}

void Clapper::start()
{
    // init buffer
    for (int index = 0; index < CLAPPER_BUFFER_LENGTH; index++)
        buffer[index] = this->pin.read();

    this->thread.start(callback(this, &Clapper::thread_func));
}
