import telebot
import serial
import os
from telebot.types import InlineKeyboardMarkup, InlineKeyboardButton

TELEGRAM_TOKEN = '2146921983:AAGmZkKD8vNH1aQUQtZ84AHsUorczAWhpNE'

bot = telebot.TeleBot(TELEGRAM_TOKEN)

class Serializer:
    #global read_state

    def __init__(self, timeout=5):
        self.ser = serial.Serial('COM10', 9600, timeout=timeout, writeTimeout=timeout)

    def open(self):
        if(self.ser.isOpen() == False):
            self.ser.open()
            print("Serial is open")
        else:
            print("Serial already open")

    def close(self):
        self.ser.close()
        print("Serial is close")

    def send(self, msg):
        self.ser.write(msg)
    
    def read_command(self):
        print("read commands")
        data = self.ser.readline().decode()
        print(data)
        if data == u'X1-GOOD\r\n':
            arduino.send(b'T1\n')
        if data == u'X2-GOOD\r\n':
            arduino.send(b'T1\n')
        if data == u'X3-GOOD\r\n':
            arduino.send(b'T1\n')
        if data == u'X4-GOOD\r\n':
           print("X4 good - send T1")
           arduino.send(b'T1\n')

        if data == u'Y1-GOOD\r\n':
            arduino.send(b'T2\n')
        if data == u'Y2-GOOD\r\n':
            arduino.send(b'T2\n')
        if data == u'Y3-GOOD\r\n':
            arduino.send(b'T2\n')
        if data == u'Y4-GOOD\r\n':
            print("Y4 good - send t2")
            arduino.send(b'T2\n')

        if data == u'Turrel X capsule - false\r\n':
            print("Turrel X capsule - false")
            nextion.send('page page0')
            nextion.send('vis 5,0')
            #read()
            self.ser.close()
        if data == u'Turrel X capsule - true\r\n':
            print("Turrel X capsule - true")
            nextion.send('page page0')
            nextion.send('vis 5,1')
            read()
            self.ser.close()
        if data == u'Turrel Y capsule - false\r\n':
            print("Turrel Y capsule - false")
            nextion.send('page page0')
            nextion.send('vis 6,0')
            read()
            self.ser.close()
        if data == u'Turrel X capsule - true\r\n':
            print("Turrel Y capsule - true")
            nextion.send('page page0')
            nextion.send('vis 6,1')
            read()
            self.ser.close()

    def recv(self):
        return self.ser.readline()

arduino = Serializer()


def gen_markup():
    markup = InlineKeyboardMarkup()
    markup.row_width = 2
    markup.add(InlineKeyboardButton("Выдать кофе Х", callback_data="sx"), InlineKeyboardButton("Выдать кофе Y", callback_data="sy"), InlineKeyboardButton("Проверить турель 1", callback_data="t1"), InlineKeyboardButton("Проверить турель 2", callback_data="t2"),InlineKeyboardButton("Сахар", callback_data="s3"), InlineKeyboardButton("Сливки", callback_data="s4"), InlineKeyboardButton("Перезагрузка", callback_data="reset"), InlineKeyboardButton("Сверка итогов", callback_data="reset_sb"))
    return markup

@bot.callback_query_handler(func=lambda call: True)
def callback_query(call):
    if call.data == "sx":
        arduino.open()
        arduino.send(b'X1\n')
        arduino.close()
        bot.answer_callback_query(call.id, "Кофе Х")
    if call.data == "sy":
        arduino.open()
        arduino.send(b'Y1\n')
        arduino.close()
        bot.answer_callback_query(call.id, "Кофе Y")
    if call.data == "t1":
        arduino.open()
        arduino.send(b'T1\n')
        arduino.close()
        bot.answer_callback_query(call.id, "Проверка турелей на капсулы")
    elif call.data == "t2":
        arduino.open()
        arduino.send(b'T2\n')
        arduino.close()
        bot.answer_callback_query(call.id, "Проверка турелей на капсулы")
    elif call.data == "s3":
        arduino.open()
        arduino.send(b'S3\n')
        arduino.close()
        bot.answer_callback_query(call.id, "Выдаю сахар")
    elif call.data == "s4":
        arduino.open()
        arduino.send(b'S4\n')
        arduino.close()
        bot.answer_callback_query(call.id, "Выдаю сливки")
    elif call.data == "reset":
        output = os.system('pm2 restart app4')
        print(output)
        bot.answer_callback_query(call.id, "Перезагрузка автозагрузки")
    elif call.data == "reset_sb":
        output = os.system('./sb_pilot 7')
        print(output)
        bot.answer_callback_query(call.id, "Сверка итогов")

@bot.message_handler(func=lambda message: True)
def message_handler(message):
    bot.send_message(message.chat.id, "Выбери команду", reply_markup=gen_markup())

bot.infinity_polling()