#include "agipo/serial.h"
#include "agipo/analog.h"
#include "agipo/digital.h"

// class PAD
// {
// private:
//     int X_pin = NULL;
//     int Y_pin = NULL;
//     int SW_pin = NULL;
//     int x = analogRead(X_pin);
//     int y = analogRead(Y_pin);
//     int sw = digitalRead(SW_pin);
//     int x1{}, y1{};

// public:
//     void set_PAD(int x, int y, int SW)
//     {
//         X_pin = x;
//         Y_pin = y;
//         SW_pin = SW;
//         //pinMode(SW_pin, INPUT_PULLUP);
//         //digitalWrite(SW_pin, LOW);
//         for (int i = 0; i < 100; i++)
//         {
//             x1 += analogRead(X_pin);
//             y1 += analogRead(Y_pin);
//         }
//         x1 = x1 / 100;
//         y1 = y1 / 100;
//     };
//     void update()
//     {
//         x = analogRead(X_pin);
//         y = analogRead(Y_pin);
//         sw = digitalRead(SW_pin);
//     };
//     int position()
//     {
//         /*
//         UP - 1
//         DOWN - 2 
//         LEFT - 3
//         RIGTH - 4
//         NONE - 0
//         */
//         update();
//         if ((x - x1) * (x - x1) + (y - y1) * (y - y1) < 4000)
//         {
//             return 0;
//         }
//         if (x >= y && x <= -y + 1023)
//         {
//             return 1;
//         }
//         if (x <= y && x >= -y + 1023)
//         {
//             return 2;
//         }
//         if (x < y && x < -y + 1023)
//         {
//             return 3;
//         }
//         if (x > y && x > -y + 1023)
//         {
//             return 4;
//         }
//     }
//     void check()
//     {
//         // Serial.print("x,y - ");
//         // Serial.print(x);
//         // Serial.print(",");
//         // Serial.print(y);
//         // Serial.print("\n");
//         // Serial.print("SW - ");
//         // Serial.print(digitalRead(SW_pin));
//         // Serial.print("\n");
//     }
// };
