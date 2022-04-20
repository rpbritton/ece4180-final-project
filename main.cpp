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
#include "dipswitch.h"

int main()
{
    //
    // create activators
    //
    Button button(p30);
    Bluetooth bluetooth(p28, p27);
    Clapper clapper(p16, 0.01);
    Photoresistor lightSense(p15);
    Sonar sonarSense(p6, p7);

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
    ServoOut servoOutput(p21);
    SpeakerOut speakerOutput(p26, 440.0, 0.2);
    Outlet outlet(p8);
    Led led(LED1);

    Output *outputs[] = {
        &servoOutput,
        &speakerOutput,
        &outlet,
        &led};
    int num_outputs = sizeof(outputs) / sizeof(outputs[0]);

    //
    // create LCD
    //
    Lcd lcd(p9, p10, p11);
    lcd.start(num_activators, activators, num_outputs, outputs);
        
    //
    // start and enable all peripherals
    //
    for (int index = 0; index < num_activators; index++)
    {
        activators[index]->start();
        activators[index]->enable(true);
        lcd.activator_enable(activators[index], true);
    }
    for (int index = 0; index < num_outputs; index++)
    {
        outputs[index]->enable(true);
        lcd.output_enable(outputs[index], true);
    }
    
    //
    // create dipswitch
    //
    Dipswitch dipswitches[8] = {
        Dipswitch(p12), 
        Dipswitch(p13), 
        Dipswitch(p14), 
        Dipswitch(p17), 
        Dipswitch(p18), 
        Dipswitch(p19), 
        Dipswitch(p20), 
        Dipswitch(p22)
    };
    for (int index = 0; index < 8; index++)
        dipswitches[index].start();
    Activator *dipswitchActivators[8] = {
        &bluetooth,
        &clapper,
        &sonarSense,
        &button,
        &lightSense,
        NULL,
        NULL,
        NULL
    };
    Output *dipswitchOutputs[8] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &servoOutput,
        &outlet,
        &speakerOutput
    };

    //
    // monitor activator states
    //
    bool lit = false;
    bool activator_states[num_activators];
    for (int index = 0; index < num_activators; index++)
        activator_states[index] = false;

    while (1)
    {
        //
        // check dipswitches
        //
        for (int index = 0; index < 8; index++)
        {
            if (!dipswitches[index].changed())
                continue;
            
            bool state = dipswitches[index].read();
            
            if (dipswitchActivators[index] != NULL)
            {
                dipswitchActivators[index]->enable(state);
                lcd.activator_enable(dipswitchActivators[index], state);
            }
            
            if (dipswitchOutputs[index] != NULL)
            {
                dipswitchOutputs[index]->enable(state);
                lcd.output_enable(dipswitchOutputs[index], state);
            }
        }
        
        //
        // check activators
        //
        bool changed = false;
        for (int index = 0; index < num_activators; index++)
        {
            activator_states[index] = activators[index]->state();
            if (activator_states[index])
                changed = true;
        }

        //
        // state changed, update
        //
        if (changed)
        {
            lit = !lit;

            //
            // update activator activation
            //
            for (int index = 0; index < num_activators; index++)
            {
                lcd.activator_activate(activators[index], activator_states[index]);
            }

            //
            // update output activation
            //
            for (int index = 0; index < num_outputs; index++)
            {
                bool active = outputs[index]->activate(lit);
                lcd.output_activate(outputs[index], active && lit);
            }
        }

        Thread::wait(1000);
    }
}
