import serial 
import time 
import struct

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate =9600,           
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

k=struct.pack('B', 0xff)
time.sleep(1)
 
command = 'dim=5'
ser.write(command.encode())
ser.write(k)
ser.write(k)
ser.write(k)