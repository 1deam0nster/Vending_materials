from subprocess import call
import serial
import time

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

ser_a1 = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)


time.sleep(1)

sugar = False


def read_t1():
    ser_a1.write(b'T1\n')
    time.sleep(10)
    output_a1 = ser_a1.readline()
    if output_a1:
        print(output_a1)
    if output_a1 == u'Turrel X capsule - true':
        # убираем на дисплее кнопку
        #call(["python3", "test2.py"])
        EndCom = "\xff\xff\xff"
        ser.write('b0.txt="Test"'+EndCom)
    if output_a1 == u'Turrel X capsule - false':
        # убираем на дисплее кнопку
        #call(["python3", "test2.py"])


read_t1()


while True:
    try:
        #output = ser.readline().decode('iso-8859-1')
        #output = ser.readline().decode('ascii')
        output = ser.readline()
#                input = input(">> ")
#                if input == 'exit':
#                        exit()
#                if input == 'g1':
#                        call(["python3", "g1.py"])
        if output:
            print(output)
            print(output.decode())
            if output == u'g1':
                print("good3")
                call(["python3", "com_x.py"])
            # Кнопка для приготовления кофе №1
            if output == b'e\x01\x05\x01\xff\xff\xff':
                print("Starting job - coffe #1")
                if sugar == True:
                    print("Starting job width sugar")
                    call(["python3", "com_x.py"])
                else:
                    print("Starting job widthout sugar")
                    call(["python3", "com_x.py"])
            # Кнопка для выдачи сахара
            if output == b'e\x01\x06\x01\xff\xff\xff' and sugar == False:
                print("sugar on")
                sugar = True
                output = None
            if output == b'e\x01\x06\x01\xff\xff\xff' and sugar == True:
                print("sugar off")
                sugar = False
                output = None
            if output == 'g1':

                print("good5")
                call(["python3", "test2.py"])
                continue
        time.sleep(0.5)

    except Exception:
        pass


# def init():
#  a = int(input())
#  while True:
#      if a == 1:
#          call(["python3", "test2.py"])
#          continue
#      if a == 2:
#          print("2")
#          import test2
#          continue
#
# init()
