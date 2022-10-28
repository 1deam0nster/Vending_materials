import serial

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
    
def read_command(self):
    print("read commands")
    data = ser.readline().decode()
    print(data)

def recv(self):
    return ser.readline()





# class Serializer:

#     def __init__(self):
#         self.ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5, writeTimeout=5)

#     def open(self):
#         if(self.ser.isOpen() == False):
#             self.ser.open()
#             print("Serial is open")
#         else:
#             print("Serial already open")

#     def close(self):
#         self.ser.close()
#         print("Serial is close")

#     def send(self, msg):
#         self.ser.write(msg)
    
#     def read_command(self):
#         print("read commands")
#         data = self.ser.readline().decode()
#         print(data)

#     def recv(self):
#         return self.ser.readline()


#if __name__ == '__main__':
    #Create class arduino and connect to
#ard = Serializer()