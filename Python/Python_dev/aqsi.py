import socket
import struct
import re
import click
import json

#Служебная информация
ADDRESS = '192.168.1.40'
PORT = 4455
BUFFER_SIZE = 4
file_path_tr = 'transaction.json'
# templ = 'command.json'
# amount = 1

#Парсинг аргумента -а при запуске скрипта
@click.command()
# @click.argument("price")
@click.option('--amount', default=1, help='Price to send in terminal.')
# @click.option('--name', prompt='Your name',
#               help='The person to greet.')
def change_json(amount):
    # click.echo(f"Price is {amount}!")
    templ = '{"command": "transaction", "type": "purchase", "currency": 0, "amount":' + str(amount) + '}'
    # print(templ)

    file = open("transaction.json", "w")
    file.write(templ)
    file.close()

    send(read(file_path_tr), file_path_tr)



# #Открываем JSON с файлом на транзакцию
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
            # print("Sent.")
        

        # Ждем ответ
        while True:
            response = s.recv(10240000)
           
            if response:
                # print('Обработка данных...')
                # print(response)
                if re.search(r'\bdeclined\b', str(response)):
                    #print("Транзакция не прошла")
                    #print(0)
                    #socket.close()
                    return False
                    #break
                if re.search(r'\bapproved\b', str(response)):
                    #print("Транзакция прошла")
                    print(1)
                    break
            else:
                print("Нет данных")
                socket.close()
                break

        return response, s


def main():
    change_json()

if __name__ == '__main__':
    main()