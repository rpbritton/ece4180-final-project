#include "photoresistor.h"

void Photoresistor::thread_func()
{
    float sensorReading;
    while(1)
    {
        this->active_lock.lock();
        bool isEnabled = this->enabled;
        this->active_lock.unlock();
        //if this peripheral is enabled, check it.
        if(isEnabled)
        {
            sensorReading = *(this->sensor);
            
            //If light is currently on, check if it needs to be turned off
            if(this->prevReading)
            {
                //sensor reading below threshold, send signal to turn off light
                if(sensorReading > 0.60)
                {
                    this->active_lock.lock();
                    this->active = true;
                    this->active_lock.unlock();
                    this->prevReading = false;
                }
                else
                {
                    //sensor reading above threshold, leave light on
                    this->prevReading = true;
                }
                
                
            }
            else
            {
                //sensor reading above threshold, send signal to turn on light
                if(sensorReading < 0.40)
                {
                    this->active_lock.lock();
                    this->active = true;
                    this->active_lock.unlock();
                    this->prevReading = true;
                }
                else
                {
                    //sensor reading above threshold, leave light off
                    this->prevReading = false;
                }
            }
        }
        Thread :: wait(500);
    }

}

bool Photoresistor::read()
{
    this->active_lock.lock();
    bool readRes = this->active;
    this->active = false;
    this->active_lock.unlock();
    return readRes;
}

void Photoresistor::enable(bool enable)
{
    this->active_lock.lock();
    this->enabled = enable;
    this->active_lock.unlock();
    return;
}

void Photoresistor::start()
{
    this->enabled = true;
    this->prevReading = false;
    this->thread.start(callback(this, &Photoresistor::thread_func));
    return;
}


