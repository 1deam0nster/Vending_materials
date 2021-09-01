import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

print ('Enter your commands below.\r\nInsert "exit" to leave the application.')

while 1 :
    # get keyboard input
    inp = input(">> ")
        # Python 3 users
        # input = input(">> ")
    if inp == 'exit':
        ser.close()
        exit()
    else:
        # send the character to the device
        # (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
        inp_str = str(inp)
        input_b = bytes(inp_str, 'utf-8')
        ser.write(input_b + b'\n')
        out = ''
        # let's wait one second before reading output (let's give device time to answer)
        time.sleep(1)
        while ser.inWaiting() > 0:
            out += ser.read(1)

        if out != '':
            print (">>" + out)

#----------------------2 code---------------------------
# import serial, time
# #initialization and open the port

# #possible timeout values:
# #    1. None: wait forever, block call
# #    2. 0: non-blocking mode, return immediately
# #    3. x, x is bigger than 0, float allowed, timeout block call

# ser = serial.Serial()
# #ser.port = "/dev/ttyUSB0"
# ser.port = "/dev/ttyUSB7"
# #ser.port = "/dev/ttyS2"
# ser.baudrate = 9600
# ser.bytesize = serial.EIGHTBITS #number of bits per bytes
# ser.parity = serial.PARITY_NONE #set parity check: no parity
# ser.stopbits = serial.STOPBITS_ONE #number of stop bits
# #ser.timeout = None          #block read
# ser.timeout = 1            #non-block read
# #ser.timeout = 2              #timeout block read
# ser.xonxoff = False     #disable software flow control
# ser.rtscts = False     #disable hardware (RTS/CTS) flow control
# ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
# ser.writeTimeout = 2     #timeout for write

# try: 
#     ser.open()
# except Exception, e:
#     print "error open serial port: " + str(e)
#     exit()

# if ser.isOpen():

#     try:
#         ser.flushInput() #flush input buffer, discarding all its contents
#         ser.flushOutput()#flush output buffer, aborting current output 
#                  #and discard all that is in buffer

#         #write data
#         ser.write("AT+CSQ")
#         print("write data: AT+CSQ")

#        time.sleep(0.5)  #give the serial port sometime to receive the data

#        numOfLines = 0

#        while True:
#           response = ser.readline()
#           print("read data: " + response)

#         numOfLines = numOfLines + 1

#         if (numOfLines >= 5):
#             break

#         ser.close()
#     except Exception, e1:
#         print "error communicating...: " + str(e1)

# else:
#     print "cannot open serial port "
