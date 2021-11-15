import time
import trio
import serial

# arbitrary, but:
# - must be in between 1024 and 65535
# - can't be in use by some other program on your computer
# - must match what we set in our echo server
data = b"g1\n"

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

disp = serial.Serial(
    port='/dev/ttyS0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

#Переменные для дальней турелли X
cream_x = False
sugar_x = False

def change_sugar_x():
    global sugar_x
    if sugar_x == False:
        sugar_x = True
        return sugar_x
    if sugar_x == True:
        sugar_x = False
        return sugar_x

def change_cream_x():
    global cream_x
    if cream_x == False:
        cream_x = True
        return cream_x
    if cream_x == True:
        cream_x == False
        return cream_x

#--------------------------------------
#-----  Вспомогательные функции   -----
#--------------------------------------
async def set_unvisible_x(disp):
    print("Set unvisible coffe button X")
    await set_home_page(disp)
    terminator = b'\xff\xff\xff'
    command = str.encode('vis 5,0')
    disp.write(command + terminator)
    print("Complited")

async def set_visible_x(client):
    print("Set unvisible coffe button X")
    await set_home_page(disp)
    terminator = b'\xff\xff\xff'
    command = str.encode('vis 5,1')
    disp.write(command + terminator)
    print("Complited")


#--------------------------------------
#-----  Переход на страницы   -----
#--------------------------------------
async def set_home_page(disp):
    terminator = b'\xff\xff\xff'
    command = str.encode('page page0')
    disp.write(command + terminator)

async def set_page_s1(client):
    print("Set page start1y")
    await client.command('page start1')
    print("Complited")

async def set_page_s2(client):
    await client.command('page start2')
    print("Complited")

async def set_page_s3(client):
    await client.command('page start3')
    print("Complited")

async def set_page_s4(client):
    await client.command('page start4')
    print("Complited")


async def ser_close(ser):
    ser.close()

async def ser_start():
    ser.open()



async def sender(ser, data):
    print("sender: started!")
    print(data)
    ser.write(data)
    await check(ser)
    await trio.sleep(1)


async def check(ser):
    #while True:
    data = ser.readline()
    if data:
        print(data)

        #await sender(ser)
        #--------убрать
        if data == b'OK\r\n':
            await trio.sleep(1)
        #--------убрать

        if data == u'B1-GOOD\r\n':
            await sender(ser, b"B3\n")
        if data == u'B2-GOOD\r\n':
            await sender(ser, b"B3\n")
        if data == u'B3-GOOD\r\n':
            await trio.sleep(5)
            await sender(ser, b"M3\n")
            await sender(ser, b"B4\n")
        if data == u'B4-GOOD\r\n':
            time.sleep(70)
            await sender(ser, b"M3\n")
            time.sleep(10)
            await sender(ser, b"B5\n")
        if data == u'B5-GOOD\r\n':
            print("Проверка капсулы")
            await sender(ser, b"T1\n")
        # if data == u'Turrel X capsule - false\r\n':
        #     #делаем невидимую кнопку
        #     ser.close()
        # if data == u'Turrel X capsule - true\r\n':
        #     #делаем видимую кнопку
        #     ser.close()



async def receiver(disp):
    print("display: started!")
    while True:
        data = disp.readline()
        print(data)
        if data == b'2':
            await ser_start()
            await sender(ser, b"G1\n")
            await sender(ser, b"B1\n")
            await set_home_page(disp)
            await set_unvisible_x(disp)
            await ser_close(ser)
        if data == b'1':
            await ser_start()
            await set_home_page(disp)
            await set_visible_x(disp)
            await ser_close(ser)




async def parent():
    global ser
    global disp
    async with trio.open_nursery() as nursery:
        print("parent: spawning sender...")
        nursery.start_soon(sender, ser, data)
        print("parent: spawning receiver...")
        nursery.start_soon(receiver, disp)


if __name__ == '__main__':
    trio.run(parent)