import serial
import time

a1 = serial.Serial('COM12', 9600)

a1.write(b'r1 n1 t20\n')
time.sleep(1)

a1.write(b'r1 n2 t50\n')
time.sleep(2)

a1.close()