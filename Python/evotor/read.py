import requests
import json
import time
import datetime


with open("check.json", "r+") as jsonFile:
    data = json.load(jsonFile)
    data['external_id'] = int(data['external_id']) + 1
    print(data['external_id'])
    str(data['external_id'])

    data['timestamp'] = datetime.datetime.now().strftime("%Y.%m.%d %H:%M:%S")
    
    jsonFile.seek(0)
    json.dump(data, jsonFile)
    jsonFile.truncate()
# print(data['external_id'])



# str(id)




#jsonFile.write(json.dumps(data))

# file = open('check.json') as json_file
# print(file)
# file_pars = json.loads(file)
# print(file_pars['external_id'])