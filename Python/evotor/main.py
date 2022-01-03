import requests
import json
import time

response = requests.get(
    'https://fiscalization.evotor.ru/possystem/v4/getToken?login=Almvndng&pass=Yaroslavskaya8')
print(response.content)

key = json.loads(response.text)

print(key['token'])

token = key['token']
print(token)

payload = {
    "external_id": "4307340",
    "receipt": {
        "client": {
            "email": "kkt@kkt.ru"
        },
        "company": {
            "email": "almvndng@gmail.com",
            "sno": "usn_income",
            "inn": "9717095235",
            "payment_address": "http://almavend.ru/"
        },
        "items": [
            {
                "name": "кофе",
                "price": 1.00,
                "quantity": 1.0,
                "sum": 1.00,
                "vat": {
                    "type": "none"
                }
            }
        ],
        "payments": [
            {
                "type": 1,
                "sum": 80.0
            }
        ],
        "total": 80.0
    },
    "timestamp": "24.12.2021 19:46:00"
}
check = requests.post("https://fiscalization.evotor.ru/possystem/v4/01-000000006464735/sell?token=eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiIwMS0wMDAwMDAwMDY0NjQ3MzUiLCJpYXQiOjE2NDAzNTUzNDQsImV4cCI6MTY0MDQ0MTc0NH0.cGAzqjFs7HKDqd-r6PJV3qv04YJkTYvm0jt1ILdda4xMP80nrU6PSDvDzxQv_gyzOCR8N29GMjElggd_yausoA", data=payload)
print(check.content)

time.sleep(30)
