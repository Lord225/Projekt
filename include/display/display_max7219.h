#pragma once
#include "display_interface.h"

class DisplayExternal : public DisplayInterface
{
public:
    DisplayExternal(int clk_pin, int data_pin, int cs_pin)
    {

    }

    void set_pixel(int x, int y, bool state) override;
    bool get_pixel(int x, int y) override;
    void flush() override;
    void init() override;
};
