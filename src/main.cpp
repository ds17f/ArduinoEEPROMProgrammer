#include <Arduino.h>
#include "serial.h"
#include "eeprom.h"

/**
 * Blink all the address lights and on the final blink hold a little longer
*/
void blinkAll(int times = 3, int onCode = 0xFFFF, int delayMs = 500, int finalDelayMs = 2000) {
    int offCode = onCode ^ 0xFFFF;
    for (int i = 0; i < times - 1; i++ ) {
        setAddress(offCode, true);
        delay(delayMs);
        setAddress(onCode, false);
        delay(delayMs);
    }

    setAddress(offCode, true);
    delay(delayMs);
    setAddress(onCode, false);
    delay(delayMs);

    // shut it off no matter what
    setAddress(0, true);
    delay(finalDelayMs);
}

void setup() {
    setupPins();

    // blink 5 times and wait 5 seconds on the last blink
    // this is the signal that we're waiting for serial to begin
    // and we can ship code during this period
    blinkAll(5, 0xFFFF, 100, 5000); 

    Serial.begin(9600);
    Serial.println("<Arduino is ready>");

    // serial is up and running, blink to notify
    blinkAll(5, 0xF0F0, 100, 1000);


    // processData();

    int start = 0x0;
    int length = 0x8000 - 1  - start;
    printContents(start, length);
}


void loop() {

}