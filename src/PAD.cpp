#include <Arduino.h>

using namespace std;

class PAD
{
private:
    int X_pin = NULL;
    int Y_pin = NULL;
    int SW_pin = NULL;
    int x = analogRead(X_pin);
    int y = analogRead(Y_pin);
    int sw = digitalRead(SW_pin);

public:
    void set_PAD(int x, int y, int SW)
    {
        X_pin = x;
        Y_pin = y;
        SW_pin = SW;
        pinMode(SW_pin, INPUT);
        digitalWrite(SW_pin, HIGH);
    };
    void update()
    {
        x = analogRead(X_pin);
        y = analogRead(Y_pin);
        sw = digitalRead(SW_pin);
    };
    string position(int druk)
    {
        update();
        if ((x - 512) ^ (2) + (y - 512) ^ (2) == 10000)
        {
            Serial.println("NONE");
            check();
            return "NONE";
        }
        if (x >= y && x <= -y + 1023)
        {
            Serial.println("UP");
            check();
            return "UP";
        }
        if (x <= y && x >= -y + 1023)
        {

            Serial.println("DOWN");
            check();
            return "DOWN";
        }
        if (x < y && x < -y + 1023)
        {

            Serial.println("LEFT");
            check();
            return "LEFT";
        }
        if (x > y && x > -y + 1023)
        {

            Serial.println("RIGHT");
            check();
            return "RIGHT";
        }
    }
    void check()
    {
        Serial.print("x,y - ");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print("\n");
        Serial.print("SW - ");
        Serial.print(digitalRead(SW_pin));
        Serial.print("\n");
        delay(1000);
    }
};
