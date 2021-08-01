import serial
import time

#Подключение экрана и МК
#a1 = serial.Serial('COM12', 9600)  

#d = serial.Serial('/dev/ttyS0', 9600)
a1 = serial.Serial('/dev/ttyACM0', 9600)  
a2 = serial.Serial('/dev/ttyACM1', 9600)  


#Код для кнопки 1
def cofe1():
  a2.write(b'g1\n')
  a1.write(b'g1\n')
  time.sleep(15)
  #---Начало
  a2.write(b'g0 z80\n')
  a2.write(b'c0\n')
  a2.write(b'g0 z120\n')
  a1.write(b's0 n7 d14\n')
  time.sleep(3)
  a1.write(b'g0 y105\n')
  a1.write(b'g0 x130\n')
  a1.write(b'g0 z30\n')
  time.sleep(4)
  a2.write(b's0 n6 d47\n')
  time.sleep(2)
  #---Получили капсулу едем к кофеварке
  a1.write(b'g0 x105\n')
  time.sleep(1)
  a1.write(b'g0 z0\n')
  time.sleep(1)
  a1.write(b'g0 x65\n')
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
  a2.write(b's0 n6 d12\n')
  time.sleep(1)
  a1.write(b'g0 z0\n')
  time.sleep(2)
  a1.write(b'r1 n7 t100\n')
  a1.write(b'g0 x15 y8\n')
  time.sleep(1)
  a1.write(b'g0 z69\n')
  time.sleep(1)
  #---Выдача стаканчика
  a1.write(b'c0\n')
  time.sleep(5)
  a1.write(b'g0 z0\n')
  time.sleep(1)
  a1.write(b'g0 x57\n')
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
  a1.write(b'g0 x65\n')
  time.sleep(1)
  a1.write(b'g0 y120\n')
  time.sleep(1)
  a2.write(b's0 n6 d0\n')
  time.sleep(1)
  a2.write(b'e0 d30000\n')
  a1.write(b'g0 x0\n')
  time.sleep(1)
  a2.write(b's2\n')
  time.sleep(1)
  a1.write(b'g1\n')
  a2.write(b'g1\n')
  init()


#Код для кнопки 2
def cofe2():
  print("2")
  init()

#Код для кнопки 3
def cofe3():
  print("3")
  init()

#Функция опроса дисплея
def init():

  #Ручной ввод
  a = int(input())
  while True:
    if a == 1:
      cofe1()
      continue
    if a == 2:
      cofe2()
      continue
    if a == 3:
      cofe3()
      continue

