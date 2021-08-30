import serial
import time

# Подключение экрана и МК
#a1 = serial.Serial('COM10', 9600)
d = serial.Serial('/dev/ttyS0', 9600)
a1 = serial.Serial('/dev/ttyACM0', 9600)
a2 = serial.Serial('/dev/ttyACM1', 9600)


# Код для кнопки 1
def cofe1():
    time.sleep(2)

    a1.write(b'G0 x20\n')
    time.sleep(1)

    a1.write(b'G0 x10\n')
    time.sleep(2)

    init()


# Код для кнопки 2
def cofe2():

    #a1.write(b'G0 y30\n')
    # time.sleep(1)

    #a1.write(b'G0 y10\n')
    # time.sleep(2)

    print("Start a2")
    a2.write(b'G0 X10 y10 Z10\n')
    time.sleep(2)

    a2.write(b'G0 X0 y0 Z0\n')
    time.sleep(2)
    init()

# Код для кнопки 2


def cofe3():
    a1.write(b'G1 \n')
    print("G1")
    time.sleep(5)

    print("Start z10")
    a1.write(b'G0 z10\n')
    time.sleep(2)

    print("Start z0")
    a1.write(b'G0 z0\n')
    time.sleep(1)

    print("Start y10")
    a1.write(b'G0 y10\n')
    time.sleep(1)

    print("Start y0")
    a1.write(b'G0 y0\n')
    time.sleep(1)

    a1.write(b'G0 x10 y10 z10\n')
    time.sleep(3)
    a1.write(b'G0 x0 y0 z0\n')

    print("Start S0 N6 D150")
    a1.write(b'S0 N6 D150\n')
    time.sleep(1)

    print("Start S0 N1 D10")
    a1.write(b'S0 N6 D10\n')
    time.sleep(1)

    init()

# Функция опроса дисплея


def init():

    # Читаем данные от дисплея
    data = d.read()
    print(data)
    a = data
    print(a.decode("utf-8"))
    disp = a.decode("utf-8")
    print(disp)
    disp_int = int(disp)
    # a = int(input())
    while True:
        if disp_int == 1:
            cofe3()
            continue
        if disp_int == 2:
            cofe2()
            continue

# Запуск цикла
init()
