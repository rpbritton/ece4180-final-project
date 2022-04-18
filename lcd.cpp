#include "lcd.h"

#define LCD_FONT_SIZE (8)
#define LCD_ACTIVATORS_TITLE ("Activators")
#define LCD_OUTPUTS_TITLE ("Outputs")
#define LCD_DESCRIPTION_COLUMN (0)
#define LCD_ENABLE_TITLE ("Ena")
#define LCD_ENABLE_COLUMN (11)
#define LCD_ACTIVE_TITLE ("Act")
#define LCD_ACTIVE_COLUMN (15)

void Lcd::write_title(int row, char *description)
{
    this->lcd->set_font_size(LCD_FONT_SIZE, LCD_FONT_SIZE);

    this->lcd->text_underline(true);
    this->lcd->locate(LCD_DESCRIPTION_COLUMN, row);
    this->lcd->puts(description);

    this->lcd->text_underline(true);
    this->lcd->locate(LCD_ENABLE_COLUMN, row);
    this->lcd->puts(LCD_ENABLE_TITLE);

    this->lcd->text_underline(true);
    this->lcd->locate(LCD_ACTIVE_COLUMN, row);
    this->lcd->puts(LCD_ACTIVE_TITLE);
}

void Lcd::write_description(int row, char *description)
{
    this->lcd->set_font_size(LCD_FONT_SIZE, LCD_FONT_SIZE);
    this->lcd->text_underline(false);
    this->lcd->locate(LCD_DESCRIPTION_COLUMN, row);
    this->lcd->puts(description);
}

void Lcd::write_state(int column, int row, bool state)
{
    this->lcd->set_font_size(LCD_FONT_SIZE, LCD_FONT_SIZE);
    this->lcd->text_underline(false);
    this->lcd->locate(column, row);
    if (state)
        this->lcd->putc('x');
    else
        this->lcd->putc(' ');
}

void Lcd::write_activator_state(Activator *activator, int column, bool state)
{
    for (int index = 0; index < this->num_activators; index++)
        if (this->activators[index] == activator)
            this->write_state(column + 1, this->activator_start_row + index, state);
}

void Lcd::write_output_state(Output *output, int column, bool state)
{
    for (int index = 0; index < this->num_outputs; index++)
        if (this->outputs[index] == output)
            this->write_state(column + 1, this->output_start_row + index, state);
}

void Lcd::start()
{
    this->lcd->cls();
    this->lcd->background_color(BLACK);

    int current_row = 0;

    this->write_title(current_row, LCD_ACTIVATORS_TITLE);
    current_row += 2;
    this->activator_start_row = current_row;
    for (int index = 0; index < num_activators; index++)
        this->write_description(current_row++, this->activators[index]->description());

    current_row += 2;
    this->write_title(current_row, LCD_OUTPUTS_TITLE);
    current_row += 2;
    this->output_start_row = current_row;
    for (int index = 0; index < num_outputs; index++)
        this->write_description(current_row++, this->outputs[index]->description());
}

void Lcd::activator_enabled(Activator *activator, bool enabled)
{
    this->write_activator_state(activator, LCD_ENABLE_COLUMN, enabled);
}

void Lcd::activator_active(Activator *activator, bool active)
{
    this->write_activator_state(activator, LCD_ACTIVE_COLUMN, active);
}

void Lcd::output_enabled(Output *output, bool enabled)
{
    this->write_output_state(output, LCD_ENABLE_COLUMN, enabled);
}

void Lcd::output_active(Output *output, bool active)
{
    this->write_output_state(output, LCD_ACTIVE_COLUMN, active);
}
