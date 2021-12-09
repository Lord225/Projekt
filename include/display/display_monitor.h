#pragma once
#include "display_interface.h"
#include "agipo/serial.h"
#include "usart.h"

class DisplayMonitor : public DisplayInterface
{
    bool _screen[8][8];
    UART_HandleTypeDef& uart;
public:
    DisplayMonitor(UART_HandleTypeDef& uart) : uart(uart) {}
    void set_pixel(int x, int y, bool state) override;
    bool get_pixel(int x, int y) override;
    void flush() override;
    void init() override;
};
