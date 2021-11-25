#pragma once
#include "display_interface.h"
#include <MD_MAX72xx.h>

class DisplayExternal : public DisplayInterface
{
    MD_MAX72XX mx;
public:
    DisplayExternal(uint8_t clk_pin, uint8_t data_pin, uint8_t cs_pin, MD_MAX72XX::moduleType_t hardware_type) :
    mx(hardware_type, data_pin, clk_pin, cs_pin)
    {}

    void set_pixel(int x, int y, bool state) override;
    bool get_pixel(int x, int y) override;
    void flush() override;
    void init() override;
};
