import socket
import struct
import time
import json
import sys
import datetime
import argparse

#шаблон для транзакции, насчет поля currency не уверен
template = b'{"command":"transaction","type":"purchase","currency":0,"amount":0}'

#Парсинг аргумента -а при запуске скрипта
parser = argparse.ArgumentParser(description='get ammount')
parser.add_argument("-a", dest="ammount", required=True, type=float, default=1)
args = parser.parse_args()
ammount = int(args.ammount)

#Служебная информация
ADDRESS = '192.168.1.122'
PORT = 4455
file_path_check = 'check_connection.json'
file_path_tr = 'transaction.json'
BUFFER_SIZE = 4

def read(file_path):
    with open(file_path, 'r') as p:
        command = p.read()
        return command

#Для изменения данных в транзации  
def change_transaction(file_path_tr, ammount, templ):
    data = json.loads(templ)
    data['ammount']= ammount
    with open(file_path_tr, 'w') as f:
        json.dump(data, f)



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
        
        response = s.recv(1024)
        print(response.decode('utf8'))
        print("Response:")
        print(response)
        return response, s

        
#Распарсивание ответа
def parse_status(resp):
    data = json.loads(resp.decode('utf8')[1:])
    print(data)
    if data['status'] =='ok':
        return True
    elif data['status']!='ok':
        return False
    else:
        with open('error.log', 'a') as f:
            f.write(resp.decode('utf8')[1:])
        sys.exit()

#Примитивное логгирование
def loggers(data):
    with open('transaction.log', 'a') as f:
        mess = 'transaction start\n'+ str(datetime.datetime.now())+'\n'+data+'\n' +'transaction end \n'
        f.write(mess)
        print('log added')


def parse_result(resp):
    data = json.loads(resp.decode('utf8')[1:])
    print(data)
    if data['status']:
        if data['status'] =="ok":
            print('yes')
            loggers(str(data['acquiringData']))
        
        elif data['status']!="ok":
            return False
    else:
        if data['message'] == "keepalive":
            return None
        with open('error.log', 'a') as f:
            f.write(resp.decode('utf8')[1:]+'\n')
        sys.exit()



def main():
    change_transaction(file_path_tr, ammount, template)
    resp_tr = None
    response,_ = send(read(file_path_check), file_path_check)
    count = 0
    while not response:
        time.sleep(1)
        count+=1
        if count==12:
            sys.exit()
    
    # if parse_status(response):
    #     resp_tr, soc = send(read(file_path_tr), file_path_tr)
    # while resp_tr!=True or resp_tr!=False:
    #     soc.recv(1024)
        



if __name__ == '__main__':
    main()