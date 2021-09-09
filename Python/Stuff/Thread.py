import threading
import serial
import time

d_ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)



terminator = b'\xff\xff\xff'

def reset_in_buffer():
    d_ser.reset_input_buffer()
    time.sleep(2)

def reset_out_buffer():
    d_ser.reset_output_buffer()
    time.sleep(2)

def t1_but_vis(val):
    reset_out_buffer()
    command = str.encode('vis b0,' + val.toString)
    d_ser.write(command + terminator)

def change_page():
    command = str.encode('page page0')
    d_ser.write(command + terminator)


def handle_data(data):
    print(data)
    if data == b'e\x01\x05\x01\xff\xff\xff':
            #запуск субпроцесса с опросом терминала оплаты если возвращает лог. ед. то продолжаем если нет то запускаем функцию для возврата на начальный экран
            print("Check turrel start")
            #start_cofe1()      
            proc = subprocess.Popen(["python3", "a_commands/start_t1.py"], stdout=subprocess.DEVNULL)
            proc.wait()
            state_t1 = check_turrel()
            if state_t1 == False:
                print("Нету капсулы в туреле Х")  #меняем картинку на дисплее в зависимости от наличия капсулы
                change_page()
                time.sleep(7)
                t1_but_unvis()
            else:
                print("Есть капсулы в туреле Х")
                change_page()
                time.sleep(2)
                t1_but_vis()
                #Меняем переменную сливок и сахара на False

        #if output == #команда возврата на начальную страницу(надо добавить в дисплее)
            #меняем значение сливок и сахара на лог. нуль.


def reading_display():
    while True:
        #d_ser.reset_input_buffer()
        output = d_ser.readline()
        if output:
            handle_data(output)



def second_thread():
    while True:
        print("prnt second thread")


#Start tread
th = threading.Thread(target=reading_display, args=(d_ser,), daemon=True)
th2 = threading.Thread(target=second_thread, daemon=True)

th.start()
th2.start()

