#include "bluetooth.h"

char *Bluetooth::name = "Bluetooth";

void Bluetooth::thread_func()
{
    while (1)
    {
        if (this->serial.readable())
        {
            if (this->serial.getc() == '!')
            {
                if (this->serial.getc() == 'B')
                {
                    char num = this->serial.getc();
                    char hit = this->serial.getc();
                    if (this->serial.getc() == char(~('!' + 'B' + num + hit)))
                    {
                        switch (num)
                        {
                        case '1':
                            if (hit == '1')
                            {
                                this->lock.lock();
                                this->activated = true;
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
    this->lock.lock();
    bool activated = this->activated;
    this->activated = false;
    this->lock.unlock();
    return activated;
}

void Bluetooth::start()
{
    this->thread.start(callback(this, &Bluetooth::thread_func));
}
