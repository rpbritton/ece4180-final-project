#include "mbed.h"
#include "rtos.h"
#include "lcd.h"
#include "button.h"
#include "bluetooth.h"
#include "clapper.h"
#include "photoresistor.h"
#include "sonar.h"
#include "speakerOut.h"
#include "servoOut.h"
#include "outlet.h"
#include "led.h"

int main()
{
    //
    // create activators
    //
    PinDetect buttonPin(p30);
    Button button(&buttonPin);

    Serial bluetoothSerial(p28, p27);
    Bluetooth bluetooth(&bluetoothSerial);

    AnalogIn clapperPin(p16);
    Clapper clapper(&clapperPin, 0.01);

    AnalogIn lightsensor(p15);
    Photoresistor lightSense(&lightsensor);

    DigitalOut trigger(p6);
    DigitalIn echo(p7);
    Timer sonar;
    Sonar sonarSense(&trigger, &echo, &sonar);

    Activator *activators[] = {
        &button,
        &bluetooth,
        &clapper,
        &lightSense,
        &sonarSense};
    int num_activators = sizeof(activators) / sizeof(activators[0]);

    //
    // create outputs
    //
    Servo servo(p21);
    ServoOut servoOutput(&servo);

    PwmOut speaker(p26);
    SpeakerOut speakerOutput(&speaker, 440.0, 0.2);

    DigitalOut outletPin(p8);
    Outlet outlet(&outletPin);

    DigitalOut ledPin(LED1);
    Led led(&ledPin);

    Output *outputs[] = {
        &servoOutput,
        &speakerOutput,
        &outlet,
        &led};
    int num_outputs = sizeof(outputs) / sizeof(outputs[0]);

    //
    // create LCD
    //
    uLCD_4DGL lcdLib(p9, p10, p11);
    Lcd lcd(&lcdLib);
    lcd.start(num_activators, activators, num_outputs, outputs);

    //
    // start activators
    //
    for (int index = 0; index < num_activators; index++)
        activators[index]->start();

    //
    // monitor activator states
    //
    bool state = false;
    bool activator_states[num_activators];
    for (int index = 0; index < num_activators; index++)
        activator_states[index] = false;

    // TODO: remove after dipswitch can automatically enable/disable
    for (int index = 0; index < num_activators; index++)
    {
        activators[index]->enable(true);
        lcd.activator_enable(index, true);
    }
    for (int index = 0; index < num_outputs; index++)
    {
        outputs[index]->enable(true);
        lcd.output_enable(index, true);
    }

    while (1)
    {
        bool changed = false;
        for (int index = 0; index < num_activators; index++)
        {
            activator_states[index] = activators[index]->state();
            if (activator_states[index])
                changed = true;
        }

        if (changed)
        {
            state = !state;

            //
            // update activator activation
            //
            for (int index = 0; index < num_activators; index++)
            {
                lcd.activator_activate(index, activator_states[index]);
            }

            //
            // update output activation
            //
            for (int index = 0; index < num_outputs; index++)
            {
                bool success = outputs[index]->activate(state);
                lcd.output_activate(index, success && state);
            }
        }

        Thread::wait(1000);
    }
}
