
from subprocess import call
import serial
import time

ser = serial.Serial(
        port='/dev/ttyS0',
        baudrate =9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1)

time.sleep(1)
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
                        if output == u'g1':
                                print("good3")
                                call(["python3", "test2.py"])
                                continue
                        if output == b'e\x01\x05\x01\xff\xff\xff':
                                print("goood4")
                                call(["python3", "test2.py"])
                        if output == 'g1':
                                print("good5")
                                call(["python3", "test.py"])
                                continue
                time.sleep(0.5)

        except Exception:
                pass






#def init():
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
#init()


