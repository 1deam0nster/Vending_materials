import serial
import time
import threading


# Читаем данные от дисплея
# data = a1.read()
# print(data)
# a = data
# print(a.decode("utf-8"))
# disp = a.decode("utf-8")
# print(disp)

# tdata = a1.read()           # Wait forever for anything
# time.sleep(1)
# data_left = a1.inWaiting()  # Get the number of characters ready to be read
# tdata += a1.read(data_left)
# print(tdata)

# disp_int = int(disp)
# time.sleep(2)
# a1.write(b'G0 x100\n')  # Write serial data via transport
# print('write')


# Читаем данные от дисплея
# tdata = a1.read()           # Wait forever for anything
# time.sleep(1)
# data_left = a1.inWaiting()  # Get the number of characters ready to be read
# tdata += a1.read(data_left)
# print(tdata)

# disp_int = int(disp)
# if b'OK' in tdata:
#     print('done')
#     a1.write(b'G0 y100\n')




def ReadTask(a1):

    while 1:
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
        

        WriteTask(c1 = 'G1')



def WriteTask(a1, com):
    # time.sleep(3)
    # print ("Inside Thread 1")
    # a1.write(b'T1\n')  # Byte ArrayTo Control a MicroProcessing Unit
    # print ("Thread 1 still going on")
    # time.sleep(10)
    # a1.write(b'G0 x10\n')

    com = def command(c1, arg1, arg2, arg3):
        arr = bytes(c1, 'utf-8')
        print(arr)
        time.sleep(8)
        a1.write(arr + b'\n')
        print ("comm write")





def Main():
    a1 = serial.Serial('COM22', 9600)
    #lck = threading.Lock()
    # c1 = 'g0'
    # arg1 = 'x0'
    # arg2 = 'y0'
    # arg3 = 'z0'
    com = 
    t1 = threading.Thread(target=ReadTask, args=[a1, ])
    t2 = threading.Thread(target=WriteTask, args=[a1, c1, arg1, arg2, arg3, ])
    print("Starting Thread 1")
    t1.start()
    print("Starting Thread 2")
    t2.start()

    # print ("=== exiting ===")

    # a1.close()


if __name__ == '__main__':

    Main()
