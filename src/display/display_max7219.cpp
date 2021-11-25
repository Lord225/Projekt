#include "display/display_max7219.h"

void DisplayExternal::set_pixel(int x, int y, bool state) 
{
    mx.setPoint(x, y, state);
}

bool DisplayExternal::get_pixel(int x, int y) 
{
    return mx.getPoint(x, y);
}

void DisplayExternal::flush() 
{
    
}

void DisplayExternal::init() 
{
    mx.begin();
}
