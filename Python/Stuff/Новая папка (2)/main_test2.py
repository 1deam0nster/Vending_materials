
import serial
import time
from subprocess import call


def init():
    # Подключение экрана и МК
    d = serial.Serial('/dev/ttyS0', 9600)
    #Читаем данные от дисплея
    time.sleep(.1)
    tdata = d.read()           # Wait forever for anything
    time.sleep(1)
    data_left = d.inWaiting()  # Get the number of characters ready to be read
    tdata += d.read(data_left)
    print(tdata)
    disp = tdata.decode("utf-8")
    print(disp)
    print(type(disp))
    a = int(input())

    while True:
        if a == 1 or repr(disp) == "1":
            print("Ok")
            call(["python3", "test2.py"])
        if a == 2 or str(disp) == "2":
            print("2")
            import test2
init()
