#include "snake/app.h"

void Application::game_over(GameState after_animation, int target_size)
{
    println("GAME OVER: " + std::to_string(after_animation) + " " + std::to_string(target_size));
    game_state = GameState::GameOverAnim;
    animations.emplace_back(std::make_unique<ScreenFlickerGameOver>(ScreenFlickerGameOver(1500.0f, 0.2f, 0.5f, this, after_animation, target_size)));
}

PAD::DIR Application::random_direction(PAD::DIR exclude)
{
    PAD::DIR dir = static_cast<PAD::DIR>((rand() % 4) + 1);
    while (dir == exclude)
        dir = static_cast<PAD::DIR>((rand() % 4) + 1);
    return dir;
}

PAD::DIR Application::get_neg_dir(PAD::DIR dir)
{
    switch (dir)
    {
    case PAD::DIR::NONE:
        return PAD::DIR::NONE;
    case PAD::DIR::RIGHT:
        return PAD::DIR::LEFT;
    case PAD::DIR::LEFT:
        return PAD::DIR::RIGHT;
    case PAD::DIR::UP:
        return PAD::DIR::DOWN;
    case PAD::DIR::DOWN:
        return PAD::DIR::UP;
    default:
        return PAD::DIR::NONE;
    }
}