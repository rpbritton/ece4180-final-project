#include "photoresistor.h"

char *Photoresistor::name = "Sunlight";

void Photoresistor::thread_func()
{
    float sensorReading;
    while (1)
    {
        sensorReading = *(this->sensor);

        // If light is currently on, check if it needs to be turned off
        if (this->prevReading)
        {
            // sensor reading below threshold, send signal to turn off light
            if (sensorReading > 0.60)
            {
                this->lock.lock();
                this->activated = true;
                this->lock.unlock();
                this->prevReading = false;
            }
            else
            {
                // sensor reading above threshold, leave light on
                this->prevReading = true;
            }
        }
        else
        {
            // sensor reading above threshold, send signal to turn on light
            if (sensorReading < 0.40)
            {
                this->lock.lock();
                this->activated = true;
                this->lock.unlock();
                this->prevReading = true;
            }
            else
            {
                // sensor reading above threshold, leave light off
                this->prevReading = false;
            }
        }
        Thread::wait(500);
    }
}

bool Photoresistor::read()
{
    this->lock.lock();
    bool activated = this->activated;
    this->activated = false;
    this->lock.unlock();
    return activated;
}

void Photoresistor::start()
{
    this->prevReading = false;
    this->thread.start(callback(this, &Photoresistor::thread_func));
}
