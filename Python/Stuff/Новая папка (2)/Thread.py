from treading import Thread, Lock
from time import sleep

def first_thread():
    a = int(input())
    while True:
        if a == 1:
            print("prnt 1")
            th2._Thread__stop()
            print("prnt 1")
            continue
        if a == 2:
            print("2")
            import test2
            continue

def second_thread():
    while True:
        print("prnt second thread")


#Start tread
th = Thread(target=first_thread)
th2 = Thread(target=second_thread, daemon=True)

th.start()
th2.start()
