import serial
import time

ser = serial.Serial('COM12', 9600)  
print(ser.name)   
time.sleep(2)

ser.write(b'L1 \n')
time.sleep(2)

ser.write(b'L2 \n')
time.sleep(1)

ser.write(b'g0 x100\n')

time.sleep(1)

ser.write(b'S0 D100\n')

ser.write(b'S0 D10\n')
time.sleep(1)

ser.close()