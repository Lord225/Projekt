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
    int x1{}, y1{};

public:
    void set_PAD(int x, int y, int SW)
    {
        X_pin = x;
        Y_pin = y;
        SW_pin = SW;
        pinMode(SW_pin, INPUT_PULLUP);
        digitalWrite(SW_pin, LOW);
        for (int i = 0; i < 100; i++)
        {
            x1 += analogRead(X_pin);
            y1 += analogRead(Y_pin);
        }
        x1 = x1 / 100;
        y1 = y1 / 100;
    };
    void update()
    {
        x = analogRead(X_pin);
        y = analogRead(Y_pin);
        sw = digitalRead(SW_pin);
    };
    enum position(int druk)
    {
        enum UP = 0;
        enum DOWN = 1;
        enum LEFT = 2;
        enum RIGHT = 4;
        update();
        if ((x - x1) * (x - x1) + (y - y1) * (y - y1) < 40000){
            Serial.println("NONE");
            check();
            return "NONE";}
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
} void check()
{
    Serial.print("x,y - ");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print("\n");
    Serial.print("SW - ");
    Serial.print(digitalRead(SW_pin));
    Serial.print("\n");
}
}
;
