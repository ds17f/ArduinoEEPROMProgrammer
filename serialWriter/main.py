import struct
import serial
import binascii
import hexdump
import time

CONTINUE = b'\xFF'

PORT = "/dev/ttyACM19"
BAUD = 9600
TIMEOUT = 1000

blockSize = 63

def read_until_ready(ser):
    '''read the serial line and see if we've got an 0xFF'''
    print("Read the serial and wait for signal to proceed")
    data = ser.read(1)
    while (data != b'\xff'):
        try:
            print(data.decode('ascii'), end='')
            data = ser.read(1)
        except serial.SerialException:
            print("failed to read")
            time.sleep(1)



def main():
    print("Starting up")
    # read the eeprom as a bytearray
    my_file = "eeprom.bin"
    with open(my_file, 'rb') as file_t:
        print("File opened")
        binary = bytearray(file_t.read())

        byte_index = 0
        with serial.Serial(PORT, BAUD, timeout=TIMEOUT) as ser:
            print("Serial opened")
            # read the file
            while(byte_index < len(binary)):

                # wait until we are signaled
                read_until_ready(ser);

                print(f"read: {blockSize} bytes starting at {byte_index}")
                # read bytes of blocksize
                for i in range(blockSize):
                    current_byte = binary[byte_index]
                    print(hex(current_byte), end="")
                    print(" ", end="")
                    ser.write(struct.pack('>B', current_byte))
                    # increment the byte_index so we keep reading new stuff
                    byte_index += 1
                print(f"\ndone reading {blockSize} more bytes, total read: {byte_index} of {len(binary)}")
                
            print("wrote all data")


if __name__ == "__main__":
    main()
    