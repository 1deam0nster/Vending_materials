import serial
import time

a1 = serial.Serial('/dev/ttyACM0', 9600)

#a1.reset_input_buffer() #flush input buffer, discarding all its contents
#a1.reset_output_buffer() #flush output buffer, aborting current output

#a2.reset_input_buffer() #flush input buffer, discarding all its contents
#a2.reset_output_buffer() #flush output buffer, aborting current output


a1.write(b'b1\n')
time.sleep(2)
a1.write(b'b2\n')
time.sleep(2)
a1.write(b'b3\n')
time.sleep(2)
a1.write(b'b4\n')
time.sleep(5)
a1.write(b'b5\n')
time.sleep(2)
a1.write(b'g1\n')
a1.write(b'T1\n')
a1.close()