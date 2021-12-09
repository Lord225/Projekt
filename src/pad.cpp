#include "agipo/serial.h"
#include "agipo/analog.h"
#include "agipo/digital.h"

class PAD
{
private:
    int X_pin = 0;
    int Y_pin = 1;
    int SW_pin = 10;
    int x{}, y{};
    int sw{};
    int x1{}, y1{}, y2{};

public:
    void set_PAD(int x, int y, int SW, int R)
    {
        X_pin = x;
        Y_pin = y;
        SW_pin = SW;
        for (int i = 0; i < 100; i++)
        {
            x1 += analogRead(GPIOA, X_pin);
            y1 += analogRead(GPIOA, Y_pin);
        }
        x1 = x1 / 100;
        y1 = y1 / 100;
        y2 = R; // y2 odpowiada za none (R koła)
    };
    void update()
    {
        x = analogRead(GPIOA, X_pin);
        y = analogRead(GPIOA, Y_pin);
        sw = digitalRead(GPIOA, SW_pin);
    };
    int position()
    {
        /*
        UP - 1
        DOWN - 2 
        LEFT - 3
        RIGTH - 4
        NONE - 0
        */
        update();
        if ((x - x1) * (x - x1) + (y - y1) * (y - y1) < y2)
        {
            return 0;
        }
        if (x >= y && x <= -y + 1023)
        {
            return 1;
        }
        if (x <= y && x >= -y + 1023)
        {
            return 2;
        }
        if (x < y && x < -y + 1023)
        {
            return 3;
        }
        if (x > y && x > -y + 1023)
        {
            return 4;
        }
    }

    bool isclicked()
    {
        return sw;
    }
};
