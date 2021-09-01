import serial
import time

ser = serial.Serial('COM36', 9600)

#a1.reset_input_buffer() #flush input buffer, discarding all its contents
#a1.reset_output_buffer() #flush output buffer, aborting current output

#a2.reset_input_buffer() #flush input buffer, discarding all its contents
#a2.reset_output_buffer() #flush output buffer, aborting current output
time.sleep(2)
ser.write(b'g1 \n')
time.sleep(5)
ser.write(b'b2\n')
time.sleep(2)
ser.write(b'b3\n')
time.sleep(2)
ser.write(b'b4\n')
time.sleep(2)
ser.write(b'b5\n')
# time.sleep(10)
# ser.write(b'b3\n')
# time.sleep(5)
# ser.write(b'b4\n')
# time.sleep(5)
# ser.write(b'b5\n')
# time.sleep(5)
# ser.write(b'g1\n')
# ser.write(b'T1\n')
ser.close()