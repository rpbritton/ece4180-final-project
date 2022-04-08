#include "mbed.h"
#include "rtos.h"
#include "PinDetect.h"
#include "button.h"
#include "bluetooth.h"

int main()
{
    DigitalOut myled1(LED1);
    PinDetect buttonPin(p30);
    Button button(&buttonPin);
    button.start();

    DigitalOut myled2(LED2);
    Serial bluetoothSerial(p28, p27);
    Bluetooth bluetooth(&bluetoothSerial);
    bluetooth.start();

    while (1)
    {
        if (button.read())
        {
            myled1 = 1;
            wait(0.5);
            myled1 = 0;
        }

        if (bluetooth.read())
        {
            myled2 = 1;
            wait(0.5);
            myled2 = 0;
        }
    }
}
