def start_com_t1():
    import serial
    import time

    ser = serial.Serial('/dev/ttyACM0', 9600)
    time.sleep(2)
    all_command_write = False
    time.sleep(2)
    ser.write(b'G1\n')
    time.sleep(5)
    ser.write(b'B1\n')
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
        all_command_write = True
                
    if data == u'Turrel X capsule - false':
        ser.close()
        return False
    if data == u'Turrel X capsule - true':
        ser.close()
        return True

# if __name__ == "__main__":
#     run_t1()