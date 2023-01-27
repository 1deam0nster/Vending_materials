import serial
import time, os, subprocess

def connect():
    global ser
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5, writeTimeout=5)
    #ser = serial.Serial('COM4', 9600, timeout=5, writeTimeout=5)

def open_serial():
    if(ser.isOpen() == False):
        ser.open()
        print("Serial is open")
    else:
        print("Serial already open")

def close():
    ser.close()
    print("Serial is close")
    return

def send(msg):
    ser.write(msg)
    
def read_command():
    print("read commands")
    data = ser.readline().decode()
    print(data)
    return data
def recv():
    return ser.readline()

#   -----------------   g-code functions   -----------------   

def send_command(com):
    command =  bytes(com, 'utf-8')
    print(command)
    connect()
    time.sleep(1)
    open_serial()
    send(command + b'\n')
    close() 

def send_command2(com, com2):
    line =  com + ' ' + com2
    command =  bytes(line, 'utf-8')
    print(command)
    connect()
    time.sleep(1)
    open_serial()
    send(command + b'\n')
    close()

def send_command3(com, com2, com3):
    line =  com + ' ' + com2 + ' ' + com3
    command =  bytes(line, 'utf-8')
    print(command)
    connect()
    time.sleep(1)
    open_serial()
    send(command + b'\n')
    close() 

def sel_turrel(id_coffe):
    command_turrel =  bytes('T1 + I%s'%id_coffe, 'utf-8')
    connect()
    time.sleep(1)
    open_serial()
    send(command_turrel + b'\n')
    while True:
        data = recv()
        if data == b'Go to position true\r\n':
            close()
            return True
        else:
            close()
            return False 










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
    if int(amount) == 1:
        print("Coffe ----- Zero Error")
    if int(amount) == 1:
        open_serial()
        time.sleep(1)
        send(b'R0 N1 T100\n')
        print("Single portion")

    if int(amount) == 2:
        open_serial()
        time.sleep(1)
        send(b'R0 N1 T100\n')
        print("Double portion")
    else:
        print("Coffe ----- Error")

def start_cream(cream):
    if int(cream) == 0:
        print("Cream g-code 0 value")
    if int(cream) == 1:
        open_serial()
        send(b'S0 N22 D100\n')
        time.sleep(2)
        send(b'S0 N22 D180\n')
        print("Cream g-code ")
    if int(cream) == 2:
        open_serial()
        print("Cream g-code")
    else:
        print("Cream ----- Error")

def start_sugar(sug):
    if int(sug) == 0:
        print("Sugar g-code 0 value")
    if int(sug) == 1:
        open_serial()
        print("Sugar g-code 1 value")
    if int(sug) == 2:
        open_serial()
        print("Sugar g-code 2 value")
    else:
        print("Sugar ----- Error")

def start_chocolate(choc):
    if int(choc) == 0:
        print("Chocolate g-code 0 value")
    if int(choc) == 1:
        open_serial()
        print("Chocolate g-code 1 value")
    if int(choc) == 2:
        open_serial()
        print("Chocolate g-code 2 value")
    else:
        print("Chocolate ----- Error")
        pass


def start_gcode(amount, cream, sug, choc, id_coffe):
    turrel_check_pos = sel_turrel(id_coffe)
    if turrel_check_pos == True:
        start_coffe(amount)
    else:
        print("Turrel_check_pos ----- Error")




        

    
    print("End of function start")
    connect()
    open_serial()
    time.sleep(1)
    send(b'T2\n')
    time.sleep(1)
    close()
    print("End of function end")
    return

def aqsi(price):
    #output = os.system('python aqsi.py --amount=' + price)
    output = 1
    if output == 0:
        #print("Транзакция не прошла из функции AQSI")
        return False

    if output == 1:
        #print("Транзакция прошла")
        return True



    

    

    
    
    # while True:
    #     data = recv()
    #     print(data)
    #     if data == b'Cap state true\r\n':
    #         print("true")
    #         send(b'C1\n')
    #         send(b'C2\n')
    #         send(b'T2\n')
    #         close()
    #         break
    #     if data == b'Cap state false\r\n':
    #         print("false")
    #         send(b'T2\n')
    #         close()
    #         break 

#   -----------------   end g-code functions   -----------------   





#AQSI Terminal start pay
# program = "python aqsi.py"
# process = subprocess.Popen(["python", "aqsi.py --amount=12"])
#----------
# output = os.system('python aqsi.py --amount=24')
# if output == str(0):
#     print("Транзакция не прошла")
# if output == 1:
#     print("Транзакция прошла")
#     print("Транзакция прошла")
