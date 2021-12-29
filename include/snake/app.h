#pragma once
#include "display/Display.h"
#include "pad.h"
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
        for (int i = 0; snake.update(static_cast<PAD::DIR>(rand() % 4 + 1)) != Snake::CollisionClass::None; i++)
            if (i > 20)
                snake.reset(4, 4);
    }

    void debug_print_input()
    {
        println(std::to_string(input.wasclicked()) + " " + std::to_string(input.isclicked()));
        println(std::to_string(input.lastpostion()) + " " + std::to_string(input.position()));
    }

    void on_update()
    {
        reset_screen();

        random_heuristic();

        debug_print_input();

        snake.render(output);
    }
};


