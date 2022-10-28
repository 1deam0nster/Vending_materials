import serial
import time
import os

sugar_x = False
cream_x = False
sugar_y = False
cream_y = False

class Display:
    def __init__(self, baudrate=9600, timeout=0.1):
        self.ser = serial.Serial(
            '/dev/ttyS0', 9600, timeout=timeout, writeTimeout=timeout)
        self.command = b''

    def open(self):
        if(self.ser.isOpen() == False):
            self.ser.open()
            print("Serial is open")
        else:
            print("Serial already open")

    def close(self):
        self.ser.close()
        print("Serial is close")

    def send(self, msg):
        command = bytes(msg, 'utf-8')
        EndCom = b"\xff\xff\xff"
        self.ser.write(command+EndCom)
        # self.ser.write(msg)

    def recv(self):
        command = self.ser.readline()
        print(command)

    def handle_data(self, data):
        #print(self.command)
        if (data == b'e\x01\x05\x01\xff\xff\xff'):
            cofe_x()
            self.command = None
            self.command = b''
        if (data == b'e\x01\x06\x01\xff\xff\xff'):
            #sugar button
            self.command = None
            self.command = b''
            global sugar_x
            if sugar_x == True:
                sugar_x = False
                print(sugar_x)
                return sugar_x
            else:
                sugar_x = True
                print(sugar_x)
                return sugar_x
        if (data == b'e\x01\x07\x01\xff\xff\xff'):
            #cream button
            self.command = None
            self.command = b''
            global cream_x
            if cream_x == True:
                cream_x = False
                print(cream_x)
                return cream_x
            else:
                cream_x = True
                print(cream_x)
                return cream_x
        #Turrel - Y
        if (data == b'e\x03\x05\x01\xff\xff\xff'):
            cofe_y()
            self.command = None
            self.command = b''
        if (data == b'e\x03\x06\x01\xff\xff\xff'):
            #sugar button
            self.command = None
            self.command = b''
            global sugar_y
            if sugar_y == True:
                sugar_y = False
                print(sugar_y)
                return sugar_y
            else:
                sugar_y = True
                print(sugar_y)
                return sugar_y
        if (data == b'e\x03\x07\x01\xff\xff\xff'):
            #cream button
            self.command = None
            self.command = b''
            global cream_y
            if cream_y == True:
                cream_y = False
                print(cream_y)
                return cream_y
            else:
                cream_y = True
                print(cream_y)
                return cream_y
    def readLine(self):
        while True:
            data = self.ser.readline()
            self.handle_data(data)

class Statement:
    def __init__(self, start_state):
        self.state = start_state
    def __call__(self):
        print(self.state)
        self.state += 1
read = Statement(0)

class Serializer:
    #global read_state

    def __init__(self, baudrate=9600, timeout=5):
        self.ser = serial.Serial('/dev/ttyACM0', 9600, timeout=timeout, writeTimeout=timeout)

    def open(self):
        if(self.ser.isOpen() == False):
            self.ser.open()
            print("Serial is open")
        else:
            print("Serial already open")

    def close(self):
        self.ser.close()
        print("Serial is close")

    def send(self, msg):
        self.ser.write(msg)
    
    def read_command(self):
        print("read commands")
        data = self.ser.readline().decode()
        print(data)
        if data == u'X1-GOOD\r\n':
            arduino.send(b'T1\n')
        if data == u'X2-GOOD\r\n':
            arduino.send(b'T1\n')
        if data == u'X3-GOOD\r\n':
            arduino.send(b'T1\n')
        if data == u'X4-GOOD\r\n':
           print("X4 good - send T1")
           arduino.send(b'T1\n')

        if data == u'Y1-GOOD\r\n':
            arduino.send(b'T2\n')
        if data == u'Y2-GOOD\r\n':
            arduino.send(b'T2\n')
        if data == u'Y3-GOOD\r\n':
            arduino.send(b'T2\n')
        if data == u'Y4-GOOD\r\n':
            print("Y4 good - send t2")
            arduino.send(b'T2\n')

        if data == u'Turrel X capsule - false\r\n':
            print("Turrel X capsule - false")
            nextion.send('page page0')
            nextion.send('vis 5,0')
            #read()
            self.ser.close()
        if data == u'Turrel X capsule - true\r\n':
            print("Turrel X capsule - true")
            nextion.send('page page0')
            nextion.send('vis 5,1')
            read()
            self.ser.close()
        if data == u'Turrel Y capsule - false\r\n':
            print("Turrel Y capsule - false")
            nextion.send('page page0')
            nextion.send('vis 6,0')
            read()
            self.ser.close()
        if data == u'Turrel X capsule - true\r\n':
            print("Turrel Y capsule - true")
            nextion.send('page page0')
            nextion.send('vis 6,1')
            read()
            self.ser.close()

    def recv(self):
        return self.ser.readline()


# Create class arduino and connect to
arduino = Serializer()
nextion = Display()

def cofe_x():
    global sugar_x
    global cream_x
    read.state = 0
    nextion.send('page page5')
    output = os.system('./sb_pilot 1 8000')
    if output == 0:
        nextion.send('page start1')
        arduino.open()
        time.sleep(0.5)
        if sugar_x == False and cream_x == False:
            print("Only coffe")
            arduino.send(b'x1\n')
        if sugar_x == True and cream_x == False:
            print("Coffe with sugar")
            arduino.send(b'x2\n')
        if sugar_x == True and cream_x == True:
            print("Coffe with sugar and crem")
            arduino.send(b'x4\n')
        if sugar_x == False and cream_x == True:
            print("Coffe with cream")
            arduino.send(b'x3\n')
            
        while True:
            if read.state == 1:
                break
            else:
                arduino.read_command()
    else:
        nextion.send('page page1')   

def cofe_y():
    global sugar_y
    global cream_y
    read.state = 0
    nextion.send('page page5')
    output = os.system('./sb_pilot 1 8000')
    if output == 0:
        nextion.send('page start1')
        arduino.open()
        time.sleep(0.5)
        if sugar_y == False and cream_y == False:
            print("Only coffe")
            arduino.send(b'y1\n')
        if sugar_y == True and cream_y == False:
            print("Coffe with sugar")
            arduino.send(b'y2\n')
        if sugar_y == True and cream_y == True:
            print("Coffe with sugar and crem")
            arduino.send(b'y4\n')
        if sugar_y == False and cream_y == True:
            print("Coffe with cream")
            arduino.send(b'y3\n')
            
        while True:
            if read.state == 1:
                break
            else:
                arduino.read_command()
    else:
        nextion.send('page page1')   




def set_button_val(nextion):
    nextion.send('page page1')
    nextion.send('bt0.val=0')
    nextion.send('bt1.val=0')
    nextion.send('page page3')
    nextion.send('bt02.val=0')
    nextion.send('bt12.val=0')
    nextion.send('page page0')
set_button_val(nextion)

def run():
    nextion.open()
    time.sleep(2)
    nextion.readLine()

if __name__ == "__main__":
    run()

