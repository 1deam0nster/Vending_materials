import serial
import invoke
import time
import threading

def ReadTask():
    print("comm read")




def WriteTask(a1):
    print("comm write")



# def add(x, y):
#     return x + y

# def func(x, y, f):
# 	return f(x, y)

# print(func(1, 2, add)) # 3


def Main():
    a1 = serial.Serial('COM22', 9600)

    t1 = threading.Thread(target=ReadTask, args=[ ])
    t2 = threading.Thread(target=WriteTask, args=[write_a1(comm, arg1, arg2, arg3), a1 ])


    print("Starting Thread 1")
    t1.start()
    print("Starting Thread 2")
    t2.start()

    # print ("=== exiting ===")

    # a1.close()


if __name__ == '__main__':

    Main()
