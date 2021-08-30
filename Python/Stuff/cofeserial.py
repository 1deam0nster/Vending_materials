import serial
import time

# Подключение экрана и МК
a1 = serial.Serial('COM12', 9600)

# d = serial.Serial('/dev/ttyS0', 9600)
# a1 = serial.Serial('/dev/ttyACM0', 9600)
# a2 = serial.Serial('/dev/ttyACM1', 9600)


# Код для кнопки 1
def cofe1():
    time.sleep(2)

    a1.write(b'G1\n')
    time.sleep(5)

    a1.write(b'G0 Z80\n')
    time.sleep(1)

    a1.write(b'S0 N8 D0\n')
    time.sleep(1)

    a1.write(b'S0 N8 D50\n')
    time.sleep(1)

    a1.write(b'S0 N9 D0\n')
    time.sleep(1)

    a1.write(b'S0 N9 D50\n')
    time.sleep(1)

    a1.write(b'G0 Z120\n')
    time.sleep(1)

    init()


# Код для кнопки 2
def cofe2():

    a1.write(b'G0 y30\n')
    time.sleep(1)

    a1.write(b'G0 y10\n')
    time.sleep(2)

    init()

# Код для кнопки 2


def cofe3():

    a1.write(b'G0 z30\n')
    time.sleep(1)

    a1.write(b'G0 z10\n')
    time.sleep(1)

    a1.write(b'G0 x30\n')
    time.sleep(1)

    a1.write(b'G0 x10\n')
    time.sleep(1)

    a1.write(b'G0 y30\n')
    time.sleep(1)

    a1.write(b'G0 y10\n')
    time.sleep(5)

    a1.write(b'G0 x50 y80 z50\n')
    time.sleep(1)
    init()

# Функция опроса дисплея


def init():

    # #Читаем данные от дисплея
    # data = d.read()
    # print data

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


# Запуск цикла
init()
