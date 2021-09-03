from subprocess import call
import serial
import time
import run_t1

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)


while True:
    output = ser.readline()
    if output:
        print(output)
        print(output.decode())
        if output == b'e\x01\x05\x01\xff\xff\xff':
            print("Starting job - coffe #1")
            state_t1 = run_t1.start_com_t1()
            if state_t1 == 1:
                #меняем картинку на дисплее в зависимости от наличия капсулы
            #отдаем команду для возврата на начальный экран дисплея 
