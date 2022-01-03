import requests
import json
import time
import datetime

response = requests.get('https://fiscalization.evotor.ru/possystem/v4/getToken?login=Almvndng&pass=Yaroslavskaya8')
# print(response.content)

key = json.loads(response.text)

# print(key['token'])

token = key['token']
# print(token)

with open("check.json", "r+") as jsonFile:
    data = json.load(jsonFile)
    data['external_id'] = int(data['external_id']) + 1
    # print(data['external_id'])
    str(data['external_id'])

    data['timestamp'] = datetime.datetime.now().strftime("%Y.%m.%d %H:%M:%S")
    
    jsonFile.seek(0)
    json.dump(data, jsonFile)
    jsonFile.truncate()

with open("check.json") as jsonSend:
    data = json.load(jsonSend)

    # print(data)


url = "https://fiscalization.evotor.ru/possystem/v4/01-000000006464735/sell?token=" + token

st = ""

def send(data, url):
    check = requests.post(url, json=data)
    print(check.content)
    ch = json.loads(check.text)
    #print(ch['status'])
    global st
    st = ch['status']
    check_status(st, data, url)


def check_status(st, data, url):
    print(st)
    if st == 'wait':
        time.sleep(5)
        print("Отправляем еще раз")
        send(data, url)
        
    if st == "done":
        print("Уже не вэит а доне!!!")
        exit()

# print(url)

        

send(data, url)
time.sleep(3)
check_status(st, data, url)
