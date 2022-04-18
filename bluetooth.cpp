#include "bluetooth.h"

void Bluetooth::thread_func()
{
    while (1)
    {
        if (this->serial->readable())
        {
            if (this->serial->getc() == '!')
            {
                if (this->serial->getc() == 'B')
                {
                    char num = this->serial->getc();
                    char hit = this->serial->getc();
                    if (this->serial->getc() == char(~('!' + 'B' + num + hit)))
                    {
                        switch (num)
                        {
                        case '1':
                            if (hit == '1')
                            {
                                this->active_lock.lock();
                                this->active = true;
                                this->active_lock.unlock();
                                this->lock.lock();
                                if (this->state == ACTIVATOR_INACTIVE)
                                    this->state = ACTIVATOR_ACTIVE;
                                this->lock.unlock();
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
        Thread::wait(50);
    }
}

bool Bluetooth::read()
{
    this->active_lock.lock();
    bool active = this->active;
    this->active = false;
    this->active_lock.unlock();
    this->lock.lock();
    bool active = false;
    if (this->state == ACTIVATOR_ACTIVE)
    {
        this->state = ACTIVATOR_INACTIVE;
        active = true;
    }
    this->lock.unlock();
    return active;
}

void Bluetooth::enable(bool enable)
{
    this->lock.lock();
    if (enable && this->state == ACTIVATOR_DISABLED)
        this->state = ACTIVATOR_INACTIVE;
    else
        this->state = ACTIVATOR_DISABLED;
    this->lock.unlock();
}

void Bluetooth::start()
{
    this->thread.start(callback(this, &Bluetooth::thread_func));
}

char *Bluetooth::name = "Bluetooth";
