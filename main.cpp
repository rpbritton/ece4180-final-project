#include "mbed.h"
#include "rtos.h"
#include "PinDetect.h"
#include "button.h"
#include "bluetooth.h"
#include "photoresistor.h"
#include "sonar.h"


int main()
{
   
    DigitalOut myled1(LED1);
    PinDetect buttonPin(p30);
    Button button(&buttonPin);
    button.start();


    Serial bluetoothSerial(p28, p27);
    Bluetooth bluetooth(&bluetoothSerial);
    bluetooth.start();

  
    AnalogIn lightsensor(p15);
    Photoresistor lightSense(&lightsensor);
    lightSense.start();
    
    DigitalOut trigger(p6);
    DigitalIn  echo(p7);
    Timer sonar;
    Sonar sonarSense(&trigger, &echo, &sonar);
    sonarSense.start();
    
    bool switchLightPhotoresistor=  false;
    bool switchLightSonar = false;
    bool switchLightButton = false;
    bool switchLightBluetooth = false;
    
    bool curLightState = false;
    

    

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
        
        //myled1 has been set up to mimic the state of the actual lightswitch for debugging purposes.
        if(switchLightPhotoresistor || switchLightSonar || switchLightButton || switchLightBluetooth)
        {
            curLightState = !curLightState;
            myled1 = curLightState;
            switchLightSonar = false;
            switchLightPhotoresistor = false;
            switchLightButton = false;
            switchLightBluetooth = false;
        }
        Thread :: wait(1000);
      
        
    }
}
