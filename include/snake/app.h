#pragma once
#include <memory>
#include <list>
#include "display/Display.h"
#include "pad.h"
#include "sprites.h"
#include "point.h"
#include "snake.h"
#include "math.h"


enum GameState
{
    Game,
    GameOverAnim,
    Random,
};


class Application
{
public:
    DisplayInterface &output;
    PAD &input;
    GameState game_state = Game;

    Application(DisplayInterface &output, PAD &input) : output(output), input(input) {}

    Snake snake;
    Point apple;

    std::list<std::unique_ptr<Animation>> animations;

    int move_failed = 0;
    int last_tick = 0;
    int no_input_period = 0;

    void reset_screen()
    {
        for (int i = 0; i < output.WIDTH; i++)
            for (int j = 0; j < output.HEIGHT; j++)
                output.set_pixel(i, j, false);
    }

    void on_start()
    {
        snake.reset(4, 4, 0);
    }

    PAD::DIR random_direction(PAD::DIR exclude = PAD::DIR::NONE);

    PAD::DIR get_neg_dir(PAD::DIR dir);

    void emmit_apple()
    {
        do
        {
            apple = Point(rand() % 8, rand() % 8);
        } while (snake.check_for_colisions(apple) != Snake::CollisionClass::None);
    }

    void random_heuristic(PAD::DIR exclude = PAD::DIR::NONE)
    {
        for (int i = 0; snake.update(random_direction(exclude)) != Snake::CollisionClass::None; i++)
            if (i > 20)
                reset_game_state(7);
    }

    void player_heuristic()
    {
        auto action = input.position();

        if (action == PAD::DIR::NONE)
            action = input.lastpostion();

        if (action == PAD::DIR::NONE)
            action = snake.get_last_dir();

        auto env_response = snake.update(action);

        if (env_response == Snake::CollisionClass::Self || env_response == Snake::CollisionClass::Stay)
            random_heuristic(get_neg_dir(action));

        if (env_response == Snake::CollisionClass::None)
            move_failed = 0;

        if (env_response == Snake::CollisionClass::Wall)
            move_failed += 1;

        if (move_failed > 1)
            game_over(GameState::Game, 0);
    }

    void reset_game_state(int initial_snake_size = 0)
    {
        snake.reset(4, 4, initial_snake_size);
        emmit_apple();
    }

    void game_over(GameState after_animation, int target_size);

    void snake_apple_update()
    {
        if (snake.try_eat_apple(apple))
            emmit_apple();
    }

    void debug_print_input()
    {
        println(std::to_string(input.wasclicked()) + " " + std::to_string(input.isclicked()));
        println(std::to_string(input.lastpostion()) + " " + std::to_string(input.position()));
    }

    void check_for_heuristic_change()
    {
        if (input.lastpostion() == PAD::DIR::NONE)
            no_input_period += 1;
        else
            no_input_period = 0;
    }

    void on_update()
    {
        reset_screen();

        check_for_heuristic_change();

        switch (game_state)
        {
        case GameState::Game:
            player_heuristic();
            if (no_input_period > 20)
            {
                reset_game_state(7);
                game_state = Random;
            }
            break;
        case GameState::Random:
            random_heuristic();
            if (no_input_period == 0)
            {
                reset_game_state(0);
                game_state = Game;
            }
            break;
        default:
            break;
        }
        snake_apple_update();

        debug_print_input();
    }

    void on_render()
    {
        snake.render(output);
        apple.render(output);
    }

    void on_animation_update()
    {
        auto time = HAL_GetTick();
        auto dt = time - last_tick;
        last_tick = time;
        println(std::to_string(dt));

        for (auto it = animations.begin(); it != animations.end(); it++)
        {
            if ((*it)->isEnded())
                it = animations.erase(it);
            else
                (*it)->Update(dt);
        }
    }
};


class ScreenFlickerGameOver : public Animation
{
    int peroids;
    float fill;
    Application *app;
    GameState target;
    int target_size;

public:
    ScreenFlickerGameOver(float lerp_time,
                          float peroid,
                          float fill,
                          Application *app,
                          GameState target,
                          int target_size) : Animation(lerp_time),
                                              peroids(1 / peroid),
                                              fill(fill),
                                              app(app),
                                              target(target),
                                              target_size(target_size)
    {
    }

    void UpdateFunction(float time, float delta_time) override
    {
        if (std::ceil(cos(3.14 * time * peroids)) > 0.5)
            for (int i = 0; i < app->output.WIDTH; i++)
                for (int j = 0; j < app->output.HEIGHT; j++)
                    app->output.set_pixel(i, j, !app->output.get_pixel(i, j));
    }
    void OnEnd() override
    {
        app->reset_game_state(target_size);
        app->game_state = target;
    }
};
