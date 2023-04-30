#ifndef __serial_cpp_
#define __serial_cpp_

#include <Arduino.h>
#include "eeprom.h"

// Example 2 - Receive with an end-marker

byte CONTINUE = 0xFF;

bool newData = false;

// void recvWithEndMarker() {
//     static byte ndx = 0;
//     byte endMarker = 0x00;
//     char rc;
//     Serial.println("Receive Begin");
//     // Serial.println("is available");
//     // Serial.println(Serial.available());
//     while (Serial.available() > 0 && newData == false) {
//         rc = Serial.read();
//         Serial.println("read data");
//         Serial.println(rc);

//         if (rc != endMarker) {
//             receivedBytes[ndx] = rc;
//             ndx++;
//             if (ndx >= numBytes) {
//                 ndx = numBytes - 1;
//             }
//         }
//         else {
//             Serial.println("End marker");
//             // receivedBytes[ndx] = '\0'; // terminate the string
//             ndx = 0;
//             newData = true;
//         }
//     }
// }

void recLength(int blockSize, byte recBytes[]) {
    int rc;
    while (Serial.available() < blockSize) {
        Serial.print("buffer has: ");
        Serial.println(Serial.available());
        // wait one second to try again
        delay(1000);
    }
    Serial.println("Buffer is full, continuing");

    // read blocks until serial is empty
    int i = 0;
    while (Serial.available() > 0) {
        // Serial.println("read data");
        rc = Serial.read();
        Serial.print(rc, HEX);
        recBytes[i] = rc;
        i++;
        delay(100);
    }
    // newline to finish printing the data
    Serial.print("\n");

    // now have all the blocks
    // clear what's on the serial input
    Serial.println("Buffer has been read");
}

void showNewData(int numBytes, byte receivedBytes[]) {
    // Serial.println("showNewData");
    // for(int i = 0; i < numBytes; i++) {
    //     setAddress(receivedBytes[i], false);
    //     delay(100);
    // }

    // setAddress(0, true);
    // newData = false;
}


void fillArray(byte array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0xFF;
    }
}

void processData() {
    // startup and listen
    int address = 0;
    int blockSize = 63;
    byte receivedBytes[blockSize];   // an array to store the received data
    int nextSignal = 0xFF;

    bool done = false;
    // message back that we're ready for the next block
    Serial.write(nextSignal);
    // loop
    while (!done) {
        Serial.println("Clearing the array");
        // wipe the array
        fillArray(receivedBytes, blockSize);
        Serial.println("recLen");
        // receive a block of data (64 bytes?)
        recLength(blockSize, receivedBytes);

        // write the block of data to the next address
        writeDataToEeprom(address, blockSize, receivedBytes, false, true);

        // bump the address offset
        Serial.print("Address offset: ");
        address = address + blockSize;
        Serial.println(address);


        // message back that we're ready for the next block
        Serial.write(nextSignal);
        // end when we reach the max value
    }

}

#endif