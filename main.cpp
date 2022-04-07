#include "mbed.h"
#include "PinDetect.h"
#include "button.h"

int main()
{
    DigitalOut myled(LED1);
    PinDetect buttonPin(p30);
    Button button(&buttonPin);
    button.start();

    while (1)
    {
        if (button.read())
        {
            myled = 1;
            wait(0.5);
            myled = 0;
        }
    }
}
