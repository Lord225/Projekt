#include <Arduino.h>
#include "PAD.cpp"
#include <cstdlib>

PAD pad1;

void setup()
{
    pad1.set_PAD(0, 1, 4);
    Serial.begin(38400);
    String lolek;
}

void loop()
{
    pad1.position(1);
    delay(1000);
}