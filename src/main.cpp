#include <Arduino.h>

void setup()
{
    Serial.begin(38400);
}

void loop()
{
    Serial.print("Hello world!\n");
    delay(1000);
}