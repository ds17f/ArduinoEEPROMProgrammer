#ifndef __serial_h__
#define __serial_h__

// void recvWithEndMarker();
void recLength(int blockSize, byte receivedBytes[]);
void showNewData(int numBytes, byte receivedBytes[]);
void processData();

#endif