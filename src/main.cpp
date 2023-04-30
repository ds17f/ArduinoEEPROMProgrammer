#include <Arduino.h>
#include "serial.h"
#include "eeprom.h"

void setup() {
    setupPins();
    delay(5000); // sleep for 5 seconds so that we can ship code if we have to

    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    setAddress(0x00, false);

    // 32760
    // processData();
    int start = 0x0;
    int length = 0x8000 - 1  - start;
    printContents(start, length);
}


void loop() {

}