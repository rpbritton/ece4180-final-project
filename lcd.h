#pragma once

#include "mbed.h"
#include "uLCD_4DGL.h"
#include "activator.h"
#include "output.h"

class Lcd
{
private:
    uLCD_4DGL lcd;

    void write_title(char row, char *title);
    void write_description(char row, char *description);
    void write_state(char column, char row, bool state);
    
    int num_activators;
    Activator **activators;
    int num_outputs;
    Output **outputs;
    
    char activators_row;
    char outputs_row;

public:
    Lcd(PinName tx, PinName rx, PinName rst) : lcd(tx, rx, rst) {};
    void start(int num_activators, Activator **activators, int num_outputs, Output **outputs);
    void activator_enable(Activator *activator, bool enabled);
    void activator_activate(Activator *activator, bool activated);
    void output_enable(Output *output, bool enabled);
    void output_activate(Output *output, bool activated);
};
