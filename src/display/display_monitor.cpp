#include "display/display_monitor.h"

void DisplayMonitor::set_pixel(int x, int y, bool state)
{
    if(is_in_bounds(x, y))
        _screen[x][y] = state;
}

bool DisplayMonitor::get_pixel(int x, int y)
{
    if(is_in_bounds(x, y))
        return _screen[x][y];
    return false;
}

void DisplayMonitor::flush()
{
    println("--------", uart);
    for (int y = 0; y < 8; y++)
    {
        char LINE[10];
        for (int x = 0; x < 8; x++)
        {
            if (get_pixel(x, y))
            {
                LINE[x] = '#';
            }
            else
            {
                LINE[x] = ' ';
            }
        }
        LINE[8] = '\r';
        LINE[9] = '\0';
        println(LINE, uart);
    }
    println("--------", uart);
}

void DisplayMonitor::init()
{
    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            _screen[x][y] = 0;
}
