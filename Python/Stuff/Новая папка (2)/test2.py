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

time.sleep(3)
#---Начало
a2.write(b'g0 z80\n')
a2.write(b'c0\n')
a2.write(b'g0 z120\n')
time.sleep(3)
a1.write(b'g0 y105\n')
a1.write(b'g0 x130\n')
time.sleep(4)
a2.write(b's0 n7 d35\n')
time.sleep(2)
a1.write(b'g0 z30\n')
time.sleep(2)
a2.write(b's0 n6 d47\n')
time.sleep(1)
#---Получили капсулу едем к кофеварке
a1.write(b'g0 x105\n')
time.sleep(1)
a1.write(b'g0 z0\n')
time.sleep(1)
a1.write(b'g0 x60\n')
time.sleep(1)
a1.write(b'g0 y37\n')
time.sleep(1)
a1.write(b'r1 n6 t100\n')
time.sleep(3)
#---Открываем кофеварку
a1.write(b'r1 n6 t100\n')
time.sleep(4)
a1.write(b'g0 z69\n')
time.sleep(3)
a2.write(b's0 n6 d15\n')
time.sleep(1)
a1.write(b'g0 z0\n')
time.sleep(2)
a1.write(b'r1 n7 t100\n')
a1.write(b'g0 x10 y8\n')
time.sleep(1)
a1.write(b'g0 z69\n')
time.sleep(1)
#---Выдача стаканчика
a1.write(b'c0\n')
time.sleep(5)
a1.write(b'g0 z0\n')
time.sleep(1)
a1.write(b'g0 x55\n')
time.sleep(1)
a1.write(b'g0 y85\n')
time.sleep(1)
a1.write(b'g0 z30\n')
time.sleep(13)
#---Ждем наливки кофе
a1.write(b'g0 z0\n')
time.sleep(1)
a1.write(b'g0 x0\n')
time.sleep(1)
a2.write(b's1\n')
time.sleep(3)
a1.write(b'g0 x75\n')
time.sleep(1)
a1.write(b'g0 y120\n')
time.sleep(3)
a2.write(b's0 n6 d0\n')
time.sleep(1)
a2.write(b'e0 d28000\n')
a1.write(b'g0 x0\n')
time.sleep(1)
a2.write(b's2\n')
time.sleep(1)
a1.write(b'g1\n')
a2.write(b'g1\n')
a2.write(b'c1\n')
a1.close()
a2.close()

