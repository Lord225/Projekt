#pragma once

class DisplayInterface
{
public:
    const int WIDTH = 8;
    const int HEIGHT = 8;
    bool is_in_bounds(int x, int y) { return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT; }

    DisplayInterface() = default;

    virtual ~DisplayInterface() = default;

    virtual void set_pixel(int x, int y, bool state) = 0;
    virtual bool get_pixel(int x, int y) = 0;
    virtual void flush() = 0;
    virtual void init() = 0;
};