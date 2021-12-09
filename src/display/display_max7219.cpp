#include "display/display_max7219.h"

void DisplayExternal::set_pixel(int x, int y, bool state)
{
    if(is_in_bounds(x, y))
        _screen[x][y] = state;
}

bool DisplayExternal::get_pixel(int x, int y)
{
    if(is_in_bounds(x, y))
        return _screen[x][y];
    
    return false;
}

void DisplayExternal::flush() 
{
    for(int row = 0; row < 8; row++)
        maxTransfer(row+1, _screen[row].to_ulong());
}

void DisplayExternal::init() 
{
    maxTransfer(MAX7219_DECODE_MODE, 0x00); 
    maxTransfer(MAX7219_BRIGHTNESS, 0x00);
    maxTransfer(MAX7219_SCAN_LIMIT, 0x0F);
    maxTransfer(MAX7219_SHUTDOWN, 0x01);
    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            _screen[x][y] = 0;
}
