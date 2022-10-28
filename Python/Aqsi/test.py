from pstats import SortKey
import socket
import struct
import time
# import json
import sys
import datetime
import argparse
import re

#Служебная информация
ADDRESS = '192.168.1.122'
PORT = 4455
BUFFER_SIZE = 4
file_path_tr = 'transaction.json'


#Открываем JSON с файлом на транзакцию
def read(file_path):
    with open(file_path, 'r') as p:
        command = p.read()
        return command

#Отправка запроса и получение ответа
def send(command, file_path):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((ADDRESS, PORT))
        s.sendall(struct.pack('>I', len(command)))
        with open(file_path, "rb") as f:
            chunk = f.read(BUFFER_SIZE)
            while chunk:
                s.send(chunk)
                chunk = f.read(BUFFER_SIZE)
            print("Sent.")
        

        # Ждем ответ
        while True:
            response = s.recv(10240000)
           
            if response:
                print('Обработка данных...')
                print(response)
                if re.search(r'\bdeclined\b', str(response)):
                    print("Транзакция не прошла")
                if re.search(r'\bapproved\b', str(response)):
                    print("Транзакция прошла")

            else:
                print("Нет данных")
                socket.close()
                break

        return response, s

def main():
    send(read(file_path_tr), file_path_tr)

if __name__ == '__main__':
    main()