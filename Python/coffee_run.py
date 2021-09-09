import asyncio
#import logging
import random
import serial
import time
from nextion import Nextion, EventType

#Переменные
sugar = False
cream = False

def change_sugar():
    global sugar
    if sugar == False:
        sugar = True
        return sugar
    if sugar == True:
        sugar = False
        return sugar

def change_cream():
    global cream
    if cream == False:
        cream = True
        return cream
    if cream == True:
        cream == False
        return cream


#Проверка дальней турели
def check_coffee():
    print("Start function check coffee 1")
    ser = serial.Serial('/dev/ttyACM0', 9600)
    time.sleep(3)
    ser.write(b'T1\n')
    data = ser.readline().decode()
    if data:
        print(data)
    if data == u'Turrel X capsule - false\r\n':
        ser.close()
        asyncio.create_task(set(client))
    if data == u'Turrel X capsule - true\r\n':
        ser.close()
        asyncio.create_task(set_visible(client))



#Делаем кофе 1(дальнее)
def start_coffee():
    ser = serial.Serial('/dev/ttyACM0', 9600)
    time.sleep(2)
    class FuncCreator:
        def __init__(self, start_state):
            self.state = start_state

        def __call__(self):
            print(self.state)
            self.state += 1

    func6 = FuncCreator(0)

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
           #Заканчиваем без проверки
           func6()
           ser.close()

           #С проверкой
           #print("Проверка капсулы")
           #ser.write(b't1')

        if data == u'Turrel X capsule - false\r\n':
            func6()
            ser.close()
            asyncio.create_task(set(client))

        if data == u'Turrel X capsule - true\r\n':
            func6()
            ser.close()
            asyncio.create_task(set_visible(client))

    def start_com_t1():
        ser.write(b'G1\n')
        ser.write(b'B1\n')
        while True:
            if func6.state == 1:
                time.sleep(5)
                break
            else:
                read()
    #Вызов
    start_com_t1()

def start_coffee_sugar():
    print("Старт кофе с сахаром")


def start_coffee_cream():
    print("Старт кофе со сливками")

def start_coffee_cr_su():
    print("Старт кофе со сливками и сахаром")

async def set(client):
    print("Set unvisible coffe button 2")
    await client.command('page page0')
    await client.command('vis 12,0')
    print("Complited")

async def set_visible(client):
    print("Set visible coffe button 2")
    await client.command('page page0')
    await client.command('vis 12,1')
    print("Complited")

async def set2(client):
    print("Set unvisible coffe button 1")
    await client.command('page page0')

def start_coffee_sugar():
    print("Старт кофе с сахаром")


def start_coffee_cream():
    print("Старт кофе со сливками")

def start_coffee_cr_su():
    print("Старт кофе со сливками и сахаром")

async def set(client):
    print("Set unvisible coffe button 2")
    await client.command('page page0')
    await client.command('vis 12,0')
    print("Complited")

async def set_visible(client):
    print("Set visible coffe button 2")
    await client.command('page page0')
    await client.command('vis 12,1')
    print("Complited")

async def set2(client):
    print("Set unvisible coffe button 1")
    await client.command('page page0')
    await client.command('vis 7,0')
    print("Complited")

def event_handler(type_, data):
    if type_ == EventType.STARTUP:
        print('We have booted up!')
    elif type_ == EventType.TOUCH:
        print('A button (id: %d) was touched on page %d' % (data.component_id, data.page_id))
        if data.component_id == 5:
            global sugar
            global cream
            #Проверка на сахар и сливки
            if sugar == True and cream == False:
                start_coffee_sugar()
            if sugar == False and cream == True:
                start_coffee_cream()
            if sugar == True and cream == True:
                start_coffee_cr_su()
            if sugar == False and cream == False:
                start_coffee()
            #Проверка на капсулы
            #print("Проверка капсулы")
            #check_coffee()
            print("All tasks completed")



        if data.component_id == 6:
            print("Меняем переменную кнопки сахар")
            change_sugar()
        if data.component_id == 7:
            print("Меняем переменную кнопки сливки")
            change_cream()
   # elif type_ == DataAttributes.01.02:
   #     print("test2")
   # logging.info('Event %s data: %s', type, str(data))

async def run(client):
    await client.connect()

    # await client.sleep()
    # await client.wakeup()

    # await client.command('sendxy=0')

    #print(await client.get('sleep'))
    #print(await client.get('field1.txt'))

    #await client.set('field1.txt', "%.1f" % (random.randint(0, 1000) / 10))
    #await client.set('field2.txt', "%.1f" % (random.randint(0, 1000) / 10))

    #await client.set('field3.txt', random.randint(0, 100))

    print('Start')

if __name__ == '__main__':
    #logging.basicConfig(
    #    format='%(asctime)s - %(levelname)s - %(message)s',
    #    level=logging.DEBUG,
    #    handlers=[
    #        logging.StreamHandler()
    #    ])
    client = Nextion('/dev/ttyS0', 9600, event_handler)
    loop = asyncio.get_event_loop()
    asyncio.ensure_future(run(client))
    loop.run_forever()