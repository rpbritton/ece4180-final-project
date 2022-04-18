#include "sonar.h"

char *Sonar::name = "Doorway";

void Sonar::thread_func()
{
    this->sonar->reset();
    // measure actual software polling timer delays
    // delay used later in time correction
    // start timer
    this->sonar->start();
    // min software polling delay to read echo pin
    while (*(this->echo) == 2)
    {
    };
    // stop timer
    this->sonar->stop();
    // read timer
    this->correction = sonar->read_us();
    while (1)
    {

        this->active_lock.lock();
        bool isEnabled = this->enabled;
        this->active_lock.unlock();
        // if this peripheral is enabled, check it.

        if (isEnabled)
        {

            *(this->trigger) = 1;
            this->sonar->reset();
            wait_us(10.0);
            *(this->trigger) = 0;
            // wait for echo high
            while (*(this->echo) == 0)
            {
            };
            // echo high, so start timer
            this->sonar->start();
            // wait for echo low
            while (*(this->echo) == 1)
            {
            };
            // stop timer and read value
            this->sonar->stop();
            // subtract software overhead timer delay and scale to cm
            int distance = (this->sonar->read_us() - this->correction) / 58.0;

            // if previous reading was door open
            if (this->prevReading)
            {
                if (distance > 100)
                {
                    // if door is now closed, change light state
                    this->active_lock.lock();
                    this->active = true;
                    this->active_lock.unlock();
                    this->prevReading = false;
                }
                else
                {
                    // door is still open
                    this->prevReading = true;
                }
            }
            // if previous reading was door closed
            else
            {
                if (distance < 100)
                {
                    // door is now open, dont change light state until door closes again
                    this->prevReading = true;
                }
                else
                {
                    // door is still closed
                    this->prevReading = false;
                }
            }
        }

        Thread ::wait(500);
    }
}

bool Sonar::read()
{
    this->active_lock.lock();
    bool readRes = this->active;
    this->active = false;
    this->active_lock.unlock();
    return readRes;
}

void Sonar::enable(bool enable)
{
    this->active_lock.lock();
    this->enabled = enable;
    this->active_lock.unlock();
    return;
}

void Sonar::start()
{
    this->enabled = true;
    this->prevReading = false;
    this->thread.start(callback(this, &Sonar::thread_func));
    return;
}
