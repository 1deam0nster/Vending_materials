# import serial
# import time

# arduino = serial.Serial("COM3",baudrate = 9600, timeout = 2)
# #arduino.open()
# print(arduino.is_open)
# time.sleep(2)

# def sendCommand(command):

#     arduino.write(bytes(b"command"))
#     done = arduino.readline()
#     doneDecoded = done.decode('ascii')
#     print(doneDecoded)
#     print(done)
#     print('done')

#     pass


#-----------------второй код из ответа к примеру
# def sendCommand(command):

#     arduino.write(bytes(command))
#     time.sleep(100)
#     done = arduino.readline()
#-----------------второй код из ответа к примеру

# while True:
#     command =input(" Write your command : ")
#     sendCommand(command)



# arduino = serial.Serial("COM3",baudrate = 9600, timeout = 2)
# arduino.open()
# print(arduino.is_open)
# time.sleep(2)
import serial
import time

a1 = serial.Serial('/dev/ttyACM0', 9600)
a2 = serial.Serial('/dev/ttyACM1', 9600)


def sendCommand(arduino_num, command):
    if str(arduino_num) == "a1":
        print(arduino_num)
        print(command)
        saveFile(arduino_num, command)
        print('write to txt file')
        writeA1(command)

    if str(arduino_num) == "a2":
        print(arduino_num)
        print(command)
        saveFile(arduino_num, command)
        print('write to txt file')
        writeA2(command)
    pass

def writeA1(command):
    command = bytes(comm, 'utf-8')
    #a1.write(command + argument1 + argument2 + argument3 b'\n')
    a1.write(command + b'\n')
    print("comm write")

def writeA2(command):
    command = bytes(comm, 'utf-8')
    #a1.write(command + argument1 + argument2 + argument3 b'\n')
    a2.write(command + b'\n')
    print("comm write")


def saveFile(arduino_num, command):
    fl = open('cmnds.txt', 'at')
    print(arduino_num + ".write(b'" + command + R"\n')", file=fl, sep=' ', end='\n')
    print("time.sleep(5)", file=fl, sep=' ', end='\n')
    #fl.write(arduino_num + ".write(" + command + ")") 
    fl.close()

while True:
    arduino_num = input(" Write number arduino : ")
    command = input(" Write g-code : ")
    sendCommand(arduino_num, command)
