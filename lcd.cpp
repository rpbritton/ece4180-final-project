#include "lcd.h"

#define LCD_FONT_SIZE (8)
#define LCD_DESCRIPTION_COLUMN (0)
#define LCD_ACTIVATORS_TITLE ("Activators")
#define LCD_OUTPUTS_TITLE ("Outputs")
#define LCD_ENABLE_COLUMN (11)
#define LCD_ENABLE_TITLE ("Ena")
#define LCD_ACTIVATED_COLUMN (15)
#define LCD_ACTIVATED_TITLE ("Act")

void Lcd::write_title(char row, char *title)
{
    this->lcd->set_font_size(LCD_FONT_SIZE, LCD_FONT_SIZE);

    this->lcd->text_underline(true);
    this->lcd->locate(LCD_DESCRIPTION_COLUMN, row);
    this->lcd->puts(title);

    this->lcd->text_underline(true);
    this->lcd->locate(LCD_ENABLE_COLUMN, row);
    this->lcd->puts(LCD_ENABLE_TITLE);

    this->lcd->text_underline(true);
    this->lcd->locate(LCD_ACTIVATED_COLUMN, row);
    this->lcd->puts(LCD_ACTIVATED_TITLE);
}

void Lcd::write_description(char row, char *description)
{
    this->lcd->set_font_size(LCD_FONT_SIZE, LCD_FONT_SIZE);
    this->lcd->text_underline(false);
    this->lcd->locate(LCD_DESCRIPTION_COLUMN, row);
    this->lcd->puts(description);
}

void Lcd::write_state(char column, char row, bool state)
{
    this->lcd->set_font_size(LCD_FONT_SIZE, LCD_FONT_SIZE);
    this->lcd->text_underline(false);
    this->lcd->locate(column + 1, row);
    if (state)
        this->lcd->putc('x');
    else
        this->lcd->putc(' ');
}

void Lcd::start(int num_activators, Activator **activators, int num_outputs, Output **outputs)
{
    this->lcd->cls();
    this->lcd->background_color(BLACK);

    int current_row = 0;

    this->write_title(current_row, LCD_ACTIVATORS_TITLE);
    current_row += 2;
    this->activators_row = current_row;
    for (int index = 0; index < num_activators; index++)
        this->write_description(current_row++, activators[index]->description());

    current_row += 2;

    this->write_title(current_row, LCD_OUTPUTS_TITLE);
    current_row += 2;
    this->outputs_row = current_row;
    for (int index = 0; index < num_outputs; index++)
        this->write_description(current_row++, outputs[index]->description());
}

void Lcd::activator_enable(int activator, bool enabled)
{
    this->write_state(LCD_ENABLE_COLUMN, this->activators_row + activator, enabled);
}

void Lcd::activator_activate(int activator, bool activated)
{
    this->write_state(LCD_ACTIVATED_COLUMN, this->activators_row + activator, activated);
}

void Lcd::output_enable(int output, bool enabled)
{
    this->write_state(LCD_ENABLE_COLUMN, this->outputs_row + output, enabled);
}

void Lcd::output_activate(int output, bool activated)
{
    this->write_state(LCD_ACTIVATED_COLUMN, this->outputs_row + output, activated);
}
