#pragma once
#include "agipo/serial.h"
#include "agipo/digital.h"
#include "adc.h"

class PAD
{
private:
    int X_pin = 0;
    int Y_pin = 1;
    int SW_pin = 10;
    int x{}, y{};
    int sw{};
    int x1{}, y1{}, y2{};
    bool was_cliced = false;

public:
    enum DIR
    {
        NONE = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    void resetstates();
    void init(int x, int y, int SW, int R);
    void update();
    PAD::DIR position();
    bool isclicked();
    bool wasclicked();
};
