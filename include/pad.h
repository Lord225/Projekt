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
void buttonreset();
void set_PAD(int x, int y, int SW, int R);
void update();
int position();
bool isclicked();
bool wasclicked();
};