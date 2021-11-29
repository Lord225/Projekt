#pragma once
#include "display/Display.h"
#include "pad.cpp"

class Application
{
public:
    DisplayInterface &output;
    PAD& gamepad;

    Application(DisplayInterface &output, PAD& gamepad) : output(output), gamepad(gamepad) {}

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