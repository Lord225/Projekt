#pragma once
#include "display_interface.h"
#include <SoftwareSerial.h>

class DisplayMonitor : public DisplayInterface
{
    bool _screen[8][8];
    Stream& serial_port;
public:
    DisplayMonitor(Stream& serial_port) : serial_port(serial_port)
    {}
    void set_pixel(int x, int y, bool state) override;
    bool get_pixel(int x, int y) override;
    void flush() override;
    void init() override;
};
