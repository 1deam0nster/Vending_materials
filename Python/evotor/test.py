import requests
import json
import time
import datetime

response = requests.get('https://fiscalization-test.evotor.ru/possystem/v4/getToken?login=RdrnMyvqg5&pass=6xJeaBkjhH')
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

# payload = {
#     "external_id": 4307342321,
#     "receipt": {
#         "client": {
#             "email": "kkt@kkt.ru"
#         },
#         "company": {
#             "email": "almvndng@gmail.com",
#             "sno": "usn_income",
#             "inn": "9717095235",
#             "payment_address": "http://almavend.ru/"
#         },
#         "items": [
#             {
#                 "name": "кофе",
#                 "price": 80.00,
#                 "quantity": 1.0,
#                 "sum": 80.00,
#                 "vat": {
#                     "type": "none"
#                 }
#             }
#         ],
#         "payments": [
#             {
#                 "type": 1,
#                 "sum": 80.0
#             }
#         ],
#         "total": 80.0
#     },
#     "timestamp": "24.12.2021 19:46:00"
# }
with open("check.json") as jsonSend:
    data = json.load(jsonSend)

    # print(data)


url = "https://fiscalization-test.evotor.ru/possystem/v4/01-000000003574813/sell?token=" + token

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


