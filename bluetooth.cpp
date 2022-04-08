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
    return active;
}

void Bluetooth::start()
{
    this->thread.start(callback(this, &Bluetooth::thread_func));
}
