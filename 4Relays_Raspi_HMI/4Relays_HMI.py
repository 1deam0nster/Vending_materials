#!/usr/bin/python3
import RPi.GPIO as GPIO
import serial 
import time 
import struct

k=struct.pack('B', 0xff)

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate =9600,           
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

pin1 = 16
pin2 = 20
pin3 = 21
pin4 = 26

GPIO.setmode(GPIO.BCM)
#Setting GPIO
GPIO.setup(pin1,GPIO.OUT)
GPIO.setup(pin2,GPIO.OUT)
GPIO.setup(pin3,GPIO.OUT)
GPIO.setup(pin4,GPIO.OUT)
GPIO.setwarnings(False)

#status tombol
global tombol1_sts
global tombol2_sts
global tombol3_sts
global tombol4_sts

tombol1_sts=False
tombol2_sts=False
tombol3_sts=False
tombol4_sts=False

#Turn off All relays
GPIO.output(pin1, 1)
GPIO.output(pin2, 1)
GPIO.output(pin3, 1)
GPIO.output(pin4, 1)

#Reset for QR
r1 = "0"
r2 = "0"
r3 = "0"
r4 = "0"


def red_button(obj_name):
	#print("Red Button")
	command = obj_name + '.bco=63488'
	ser.write(command.encode())
	ser.write(k)
	ser.write(k)
	ser.write(k)

def reset_button(obj_name):
	#print("Reset Button")
	command = obj_name + '.bco=48631'
	ser.write(command.encode())
	ser.write(k)
	ser.write(k)
	ser.write(k)

def qr_code(str_code):
	command = 'qr0.txt="' + str_code + '"'
	ser.write(command.encode())
	ser.write(k)
	ser.write(k)
	ser.write(k)

def text(str):
	command = 't0.txt="' + str + '"'
	ser.write(command.encode())
	ser.write(k)
	ser.write(k)
	ser.write(k)

#Reset button
reset_button('b0')
reset_button('b1')
reset_button('b2')
reset_button('b3')

#Reset QR Code
str_code = "Relays: " + r1 + r2 + r3 + r4
qr_code(str_code)

#Reset Text
text(str_code)

#Set brightness
command = 'dim=5'
ser.write(command.encode())
ser.write(k)
ser.write(k)
ser.write(k)

time.sleep(1)

while True: 
	try:
		output = ser.readline()
		#Cek apakah ada trigger dari HMI
		if output:
			#print(output)
			#jika tombol1
			if output == b'e\x00\x02\x00\xff\xff\xff':
				print("Test good")

			
			if output == b'e\x00\x02\x01\xff\xff\xff':
				print("Tombol 2 ditekan")
				if tombol2_sts==False:
					print("Relay 2 ON")
					#turn on relay2
					GPIO.output(pin2, 0)
					tombol2_sts = True
					#Change button to red
					red_button('b1')
					r2 = "1"
				else:
					#turn off relay2
					GPIO.output(pin2, 1)
					print("Relay 2 OFF")
					tombol2_sts = False
					#Reset button
					reset_button('b1')
					r2 = "0"

			if output == b'e\x00\x05\x01\xff\xff\xff':
				print("Tombol 3 ditekan")
				if tombol3_sts==False:
					print("Relay 3 ON")
					#turn on relay3
					GPIO.output(pin3, 0)
					tombol3_sts = True
					#Change button to red
					red_button('b2')
					r3 = "1"
				else:
					#turn off relay3
					GPIO.output(pin3, 1)
					print("Relay 3 OFF")
					tombol3_sts = False
					#Reset button
					reset_button('b2')
					r3 = "0"

			if output == b'e\x00\x06\x01\xff\xff\xff':
				print("Tombol 4 ditekan")
				if tombol4_sts==False:
					print("Relay 4 ON")
					#turn on relay3
					GPIO.output(pin4, 0)
					tombol4_sts = True
					#Change button to red
					red_button('b3')
					r4 = "1"
				else:
					#turn off relay4
					GPIO.output(pin4, 1)
					print("Relay 4 OFF")
					tombol4_sts = False
					#Reset button
					reset_button('b3')
					r4 = "0"

			if output == b'e\x00\x07\x01\xff\xff\xff':
				print("Tombol Reset ditekan")
				#Turn off All relays
				GPIO.output(pin1, 1)
				GPIO.output(pin2, 1)
				GPIO.output(pin3, 1)
				GPIO.output(pin4, 1)

				#Reset button
				reset_button('b0')
				reset_button('b1')
				reset_button('b2')
				reset_button('b3')

				#Reset status
				tombol1_sts=False
				tombol2_sts=False
				tombol3_sts=False
				tombol4_sts=False

				#Reset for QR
				r1 = "0"
				r2 = "0"
				r3 = "0"
				r4 = "0"

			#Set QR Code
			str_code = "Relays: " + r1 + r2 + r3 + r4
			qr_code(str_code)
			text(str_code)




	except Exception:
		pass