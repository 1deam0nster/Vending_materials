import serial
import time
import os


"""
Manage the USB connexion.
"""
class arduino:
    # id_coffe = 1
    # command_turrel =  bytes('T1 + I%s'%id_coffe, 'utf-8')
    # home_turrel = command_turrel + b'\n'

    # com = 't2'
    # command =  bytes(com, 'utf-8')


    def __init__(self):
        self.serial = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=10, writeTimeout=0)


    def select_turrel(self, id):
        command_turrel =  bytes('T1 + I%s'%id, 'utf-8')
        home_turrel = command_turrel + b'\n'
        self.write(home_turrel)

        while True:
            data = self.recv()
            print(data)
            b'Go to position true\r\n'
            if data == b'Go to position true\r\n':
                print("true")
                break
            if data == b'Go to position false\r\n':
                print("false")
                break  
        print("select_turrel OK")
        return True

    def open(self):
        if(self.serial.isOpen() == False):
            self.serial.open()
            print("Serial is open")
        else:
            print("Serial already open")

    def close(self):
        self.serial.close()
        print("Serial is close")

    def read(self):
        try:
            return self.serial.readline().decode("ascii", "ignore")
        except OSError:
            time.sleep(1)
            return self.read()

    def recv(self):
        return self.serial.readline()

    def write(self, msg):
        self.serial.write(msg)
        print("Write")


def aqsi(price):
    #output = os.system('python aqsi.py --amount=' + price)
    output = 1
    if output == 0:
        #print("Транзакция не прошла из функции AQSI")
        return False

    if output == 1:
        #print("Транзакция прошла")
        return True

def bye_command(amount, price, cream, sug, choc, id_coffe):
    # print("Порция:", amount)
    # print("Цена:", price)
    # print("Сливки:", cream)
    # print("Шоколад:", choc)
    # print("Сахар:", sug)
    # print("ID:", id_coffe)
    # print("G-code:",g_code)


    # cream = int(0 if cream is None else cream)
    # sug = int(0 if sug is None else sug)
    # command = bytes(g_code, 'utf-8')
    # command_turrel =  bytes('T1 + I%s'%id_coffe, 'utf-8')
    # send(command_turrel + b'\n')
    
    # connect()
    # time.sleep(1)
    # open_serial()
    # sel_turrel(id_coffe)  
    
    check_payment = aqsi(price)
    if check_payment == True:
        return True
    else:
        return False

def start_coffe(amount):
    if int(amount) == 0:
        print("Coffe ----- Zero Error")
    if int(amount) == 1:
        print("Single portion")
        return True
    if int(amount) == 2:
        print("Double portion")
        return True


def start_cream(cream):
    if int(cream) == 0:
        print("Cream g-code 0 value")
        return True
    if int(cream) == 1:
        print("Cream g-code ")
        return True
    if int(cream) == 2:
        print("Cream g-code")
        return True


def start_sugar(sug):
    if int(sug) == 0:
        print("Sugar g-code 0 value")
        return True
    if int(sug) == 1:
        print("Sugar g-code 1 value")
        return True
    if int(sug) == 2:
        print("Sugar g-code 2 value")
        return True


def start_chocolate(choc):
    if int(choc) == 0:
        print("Chocolate g-code 0 value")
        return True
    if int(choc) == 1:
        print("Chocolate g-code 1 value")
        return True
    if int(choc) == 2:
        print("Chocolate g-code 2 value")
        return True



def start_gcode(amount, cream, sug, choc, id_coffe):
    cmd = arduino()
    cmd.open()
    time.sleep(1)
    cmd.write(b'T2\n')
    cmd.select_turrel(id_coffe)
    cmd.write(b'C0\n')
    start_coffe(amount)
    start_cream(cream)
    start_sugar(sug)
    start_chocolate(choc)
    cmd.write(b'T2\n')
    cmd.close()

    # turrel_check_pos = send.send(b'T1 I%s'%id_coffe\n')
    # if turrel_check_pos == True:
    #     start_coffe(amount)
    # else:
    #     print("Turrel_check_pos ----- Error")
    return


