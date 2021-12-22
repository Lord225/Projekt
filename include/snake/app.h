#pragma once
#include "display/Display.h"
#include "pad.cpp"
#include "sprites.h"
#include "point.h"
#include "snake.h"

class Application
{
public:
    DisplayInterface &output;
    PAD &input;

    Application(DisplayInterface &output, PAD &input) : output(output), input(input) {}

    Snake snake;

    void reset_screen()
    {
        for (int i = 0; i < output.WIDTH; i++)
        {
            for (int j = 0; j < output.HEIGHT; j++)
            {
                output.set_pixel(i, j, false);
            }
        }
    }

    void on_start()
    {
        snake.reset(4, 4);
    }

    void random_heuristic()
    {
        for (int i = 0; snake.update(static_cast<Snake::Direction>(rand() % 4 + 1)) != Snake::CollisionClass::None; i++)
            if (i > 20)
                snake.reset(4, 4);
    }

    void on_update()
    {
        reset_screen();

        random_heuristic();

        snake.render(output);
    }
};


