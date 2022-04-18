#include "mbed.h"
#include "rtos.h"
#include "PinDetect.h"
#include "button.h"
#include "bluetooth.h"
#include "clapper.h"
#include "photoresistor.h"
#include "sonar.h"
#include "speakerOut.h"
#include "servoOut.h"
#include "outlet.h"

int main()
{

    DigitalOut myled1(LED1);
    PinDetect buttonPin(p30);
    Button button(&buttonPin);
    button.start();

    Serial bluetoothSerial(p28, p27);
    Bluetooth bluetooth(&bluetoothSerial);
    bluetooth.start();

    AnalogIn clapperPin(p16);
    Clapper clapper(&clapperPin);
    clapper.start();

    AnalogIn lightsensor(p15);
    Photoresistor lightSense(&lightsensor);
    lightSense.start();

    DigitalOut trigger(p6);
    DigitalIn echo(p7);
    Timer sonar;
    Sonar sonarSense(&trigger, &echo, &sonar);
    sonarSense.start();

    bool switchLightPhotoresistor = false;
    bool switchLightSonar = false;
    bool switchLightButton = false;
    bool switchLightBluetooth = false;
    bool switchLightClapper = false;

    bool curLightState = false;

    Servo servo(p21);
    ServoOut servoOutput(&servo);

    PwmOut speaker(p26);
    SpeakerOut speakerOutput(&speaker, 440.0, 0.2);

    DigitalOut outletPin(p8);
    Outlet outlet(&outletPin);

    while (1)
    {

        if (button.read())
        {
            switchLightButton = true;
        }

        if (bluetooth.read())
        {
            switchLightBluetooth = true;
        }

        if (lightSense.read())
        {
            switchLightPhotoresistor = true;
        }

        if (sonarSense.read())
        {
            switchLightSonar = true;
        }

        if (clapper.read())
        {
            switchLightClapper = true;
        }

        // myled1 has been set up to mimic the state of the actual lightswitch for debugging purposes.
        if (switchLightPhotoresistor || switchLightSonar || switchLightButton || switchLightBluetooth || switchLightClapper)
        {
            curLightState = !curLightState;
            servoOutput.set(true);
            speakerOutput.set(true);
            myled1 = curLightState;
            outlet.set(curLightState);
            switchLightSonar = false;
            switchLightPhotoresistor = false;
            switchLightButton = false;
            switchLightBluetooth = false;
            switchLightClapper = false;
        }
        Thread ::wait(1000);
    }
}
