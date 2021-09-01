import serial 
import time 

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate =9600,           
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

time.sleep(1) 
while True: 
	try:
		output = ser.readline().decode(ascii)
		print(output)
		if output:
			print(output)
			if output == b'e\x01\x05\x01\xff\xff\xff ':
				print("good")
			if output == b'e\x01\x05\x01\xff\xff\xff':
				print("goood2")
			if output == 'e\x01\x05\x01\xff\xff\xff':
				print("good3")
				import test2.py
		time.sleep(0.5)

	except Exception:
		pass
