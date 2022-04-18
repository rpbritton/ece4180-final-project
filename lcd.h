#pragma once

#include "mbed.h"
#include "uLCD_4DGL.h"
#include "activator.h"
#include "output.h"

class Lcd
{
private:
    uLCD_4DGL *lcd;

    void write_title(char row, char *title);
    void write_description(char row, char *description);
    void write_state(char column, char row, bool state);
    
    char activators_row;
    char outputs_row;

public:
    Lcd(uLCD_4DGL *lcdLib) : lcd(lcdLib) {};
    void start(int num_activators, Activator **activators, int num_outputs, Output **outputs);
    void activator_enable(int activator, bool enabled);
    void activator_activate(int activator, bool activated);
    void output_enable(int output, bool enabled);
    void output_activate(int output, bool activated);
};
