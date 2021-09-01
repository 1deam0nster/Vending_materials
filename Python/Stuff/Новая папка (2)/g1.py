import serial
import time

#Подключение экрана и МК
#a1 = serial.Serial('COM12', 9600)  

#d = serial.Serial('/dev/ttyS0', 9600)
a1 = serial.Serial('/dev/ttyACM0', 9600)  
a2 = serial.Serial('/dev/ttyACM1', 9600)  

a1.flushInput() #flush input buffer, discarding all its contents
a1.flushOutput() #flush output buffer, aborting current output 

a2.flushInput() #flush input buffer, discarding all its contents
a2.flushOutput() #flush output buffer, aborting current output 



time.sleep(2)

a2.write(b'g1\n')
a1.write(b'g1\n')

time.sleep(1)
a1.close()
a2.close()
