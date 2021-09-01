import serial
import time

# Подключение экрана и МК
#a1 = serial.Serial('COM12', 9600)

d = serial.Serial('/dev/ttyS0', 9600)
a1 = serial.Serial('/dev/ttyACM0', 9600)
a2 = serial.Serial('/dev/ttyACM1', 9600)


#Читаем данные от ардуино №1
def read_a1():
    tdata = a1.read()           # Wait forever for anything
    time.sleep(1)
    data_left = a1.inWaiting()  # Get the number of characters ready to be read
    tdata += a1.read(data_left)
    print(tdata)
    disp = tdata.decode("utf-8")
    print(disp)
    print(type(disp))
    if str(disp) == "OK!":
        print("ОК - пришло")
    else:
        print("хуйня")

#Пишем данные в ардуино №1
def write_a1(comm, arg1, arg2, arg3):
    command = bytes(comm, 'utf-8')
    argument1 = bytes(arg1, 'utf-8')
    argument2 = bytes(arg2, 'utf-8')
    argument3 = bytes(arg3, 'utf-8')
    print(command)
    time.sleep(1)
    #a1.write(command + argument1 + argument2 + argument3 b'\n')
    a1.write(command + b'\n')
    print("comm write")

# Код для кнопки 1
def cofe1():
    time.sleep(2)

    write_a1("g1", "x0", "y0", "z0")
    read_a1()
    time.sleep(3)

   # write_a1(g1)
    #read_a1()
    a1.write(b'G0 x10\n')
    time.sleep(2)

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

