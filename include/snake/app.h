#pragma once
#include "display/Display.h"
#include "pad.cpp"

class Application
{
public:
    DisplayInterface &output;
    PAD& input;

    Application(DisplayInterface &output, PAD& input) : output(output), input(input) {}

    void on_start()
    {
        for (int y = 0; y < output.HEIGHT; y++)
        {
            for (int x = 0; x < output.WIDTH; x++)
            {
                output.set_pixel(x, y, (x + y + 1) % 2);
            }
        }
    }

    void change_state()
    {
        for (int y = 0; y < output.HEIGHT; y++)
        {
            for (int x = 0; x < output.WIDTH; x++)
            {
                output.set_pixel(x, y, !output.get_pixel(x, y));
            }
        }
    }

    void on_update()
    {
        if(input.isclicked())
        {  
            change_state();
        }
    }
};