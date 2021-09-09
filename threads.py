import time
import threading
import serial
#lets check com port name
#port name should ttyACM0

ser=serial.Serial('/dev/ttyACM0',115200)

def serial_handle(thread_name,timeOut):
    while(1):
        incomming_data=ser.readline() #it read one single line
        print(incomming_data)

def thread_one(thread_name,timeOut):
    while(1):
        print "Test"
        time.sleep(timeOut)

threading.start_new_thread(thread_one,("this_is_1",1))
threading.start_new_thread(serial_handle,("this_is_2",1))