import json

# read file
def read_db():
    with open('data.json', 'r', encoding='utf-8' ) as myfile:
        data = myfile.read()
    obj = json.loads(data)
    return obj

# def read_all():
#     for i in obj['Melozio']:
#         print(i)
#     return i