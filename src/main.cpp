#include <Arduino.h>
<<<<<<< HEAD
#include <iostream>
#include "display/Display.h"
#include "app.h" 

//#define USE_MONITOR_AS_DISPLAY
#define TIME_PER_FRAME_MS 100

#ifdef USE_MONITOR_AS_DISPLAY
DisplayMonitor displ = DisplayMonitor(Serial);
#else
DisplayExternal displ = DisplayExternal((uint8_t)13, (uint8_t)11, (uint8_t)10, MD_MAX72XX::GENERIC_HW);
#endif

Application app = Application(displ);
=======
#include "PAD.cpp"
#include <cstdlib>

PAD pad1;
>>>>>>> 174bc746969bf217c9f3ca70ce54eaae53e07969

void setup()
{
    pad1.set_PAD(0, 1, 4);
    Serial.begin(38400);
<<<<<<< HEAD
    displ.init();
    app.on_start();
=======
    String lolek;
>>>>>>> 174bc746969bf217c9f3ca70ce54eaae53e07969
}

void loop()
{
<<<<<<< HEAD
    const uint32_t start = millis();

    app.on_update();
    displ.flush();

    const uint32_t end = millis();

    const uint32_t delta = start - end;

    delay(max((uint32_t)1, (uint32_t)TIME_PER_FRAME_MS));
}
=======
    pad1.position(1);
    delay(1000);
}
>>>>>>> 174bc746969bf217c9f3ca70ce54eaae53e07969
