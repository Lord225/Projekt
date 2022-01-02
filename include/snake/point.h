#pragma once
#include "sprites.h"
#include <utility>

class Point : public DrawableInferface
{
public:
    enum State
    {
        high,
        low,
        contrast,
    };

    int x;
    int y;
    State state;
    Point(int sx, int sy, State state = State::high) : x(sx), y(sy), state(state) {}
    Point() : Point(0, 0) {}

    void render(DisplayInterface &render_on)
    {
        switch (state)
        {
        case State::high:
            render_on.set_pixel(x, y, true);
            break;
        case State::low:
            render_on.set_pixel(x, y, false);
            break;
        case State::contrast:
            render_on.set_pixel(x, y, !render_on.get_pixel(x, y));
            break;
        }
    }
    Point &operator=(Point const &) = default;
    Point &operator=(std::initializer_list<int> &&op)
    {
        x = *op.begin();
        y = *(op.begin() + 1);
        return *this;
    }
    Point &operator=(std::pair<int, int> &&op)
    {
        x = op.first;
        y = op.second;
        return *this;
    }
    Point &operator+=(std::pair<int, int> &&op)
    {
        x += op.first;
        y += op.second;
        return *this;
    }
    bool operator==(const Point &other)
    {
        return this->x == other.x && this->y == other.y;
    }
};