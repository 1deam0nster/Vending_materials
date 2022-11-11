import serial
import time

def connect():
    global ser
    # ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5, writeTimeout=5)
    ser = serial.Serial('COM4', 9600, timeout=5, writeTimeout=5)

def open_serial():
    if(ser.isOpen() == False):
        ser.open()
        print("Serial is open")
    else:
        print("Serial already open")

def close():
    ser.close()
    print("Serial is close")

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

def bye_command(cream, sug, id_coffe, g_code):
    print("Сливки:", cream)
    print("Сахар:",type(sug))
    print("ID:",type(id_coffe))
    print("G-code:",g_code)

    cream = int(0 if cream is None else cream)
    sugar = int(0 if sug is None else sug)
    command = bytes(g_code, 'utf-8')
    command_turrel =  bytes('T1 + I%s'%id_coffe, 'utf-8')
    
    connect()
    time.sleep(1)
    open_serial()
    if cream == 1:
        print("Cream g-code")
        
    if sugar == 1:
        print("Sugar g-code 1 value")
        
    if sugar == 2:
        print("Sugar g-code 2 value")
        send(b'T2\n')
    
    send(command_turrel + b'\n')

    send(b'C0\n')
    while True:
        data = recv()
        print(data)
        if data == b'Cap state true\r\n':
            print("true")
            send(b'C1\n')
            send(b'C2\n')
            send(b'T2\n')
            close()
            break
        if data == b'Cap state false\r\n':
            print("false")
            send(b'T2\n')
            close()
            break 

#   -----------------   end g-code functions   -----------------   