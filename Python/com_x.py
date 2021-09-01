import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)

#a1.reset_input_buffer() #flush input buffer, discarding all its contents
#a1.reset_output_buffer() #flush output buffer, aborting current output

#a2.reset_input_buffer() #flush input buffer, discarding all its contents
#a2.reset_output_buffer() #flush output buffer, aborting current output
time.sleep(2)
all_command_write = 0
time.sleep(2)
ser.write(b'G1\n')
time.sleep(5)
ser.write(b'B1\n')
def read():
    data = ser.readline().decode()
    if data:
        print(data)
    if data == u'B1-GOOD\r\n':
        ser.write(b'B3\n')
    if data == u'B3-GOOD\r\n':
        ser.write(b'B4\n')
    if data == u'B4-GOOD\r\n':
        ser.write(b'B5\n')
    if data == u'B5-GOOD\r\n':
        ser.write(b'B6\n')
        all_command_write = 1
        ser.close()
        return all_command_write

while True:
    try:
        if all_command_write == 1:
            break
        else:
            read()
    except Exception:
        pass