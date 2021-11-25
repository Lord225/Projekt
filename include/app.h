#pragma once
#include "display/Display.h"

class Application
{
public:
    DisplayInterface& output;

    Application(DisplayInterface& output) : output(output) {}

    void on_start()
    {
        for (int y = 0; y < output.HEIGHT; y++)
        {
            for (int x = 0; x < output.WIDTH; x++)
            {
                output.set_pixel(x, y, (x+y+1)%2);
            }
        }
    }

    void on_update()
    {
        for (int y = 0; y < output.HEIGHT; y++)
        {
            for (int x = 0; x < output.WIDTH; x++)
            {
                output.set_pixel(x, y, !output.get_pixel(x, y));
            }
        }
        
    }
};