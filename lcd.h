#pragma once

#include "mbed.h"
#include "uLCD_4DGL.h"
#include "activator.h"
#include "output.h"

class Lcd
{
private:
    uLCD_4DGL *lcd;

    Activator **activators;
    int num_activators;

    Output **outputs;
    int num_outputs;

    void write_title(int row, char *description);
    void write_description(int row, char *description);
    void write_state(int column, int row, bool state);
    void write_activator_state(Activator *activator, int column, bool state);
    void write_output_state(Output *output, int column, bool state);
    int activator_start_row;
    int output_start_row;

public:
    Lcd(uLCD_4DGL *lcdLib, Activator **activators, int num_activators, Output **outputs, int num_outputs) : lcd(lcdLib), activators(activators), num_activators(num_activators), outputs(outputs), num_outputs(num_outputs){};
    void start();
    void activator_enabled(Activator *activator, bool enabled);
    void activator_active(Activator *activator, bool active);
    void output_enabled(Output *output, bool enabled);
    void output_active(Output *output, bool active);
};
