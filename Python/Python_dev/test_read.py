import json

# read file
with open('data.json', 'r') as myfile:
    data = myfile.read()

# parse file
obj = json.loads(data)

# доступ к внутренним атрибутам json
cofe_1 = obj['Melozio']
print(cofe_1['description'])
print(obj['Melozio']['description'])

print("-----------------------------")
# Перечень всех атрибутов одного сорта кофе
for items in obj:
    print(items)

print("-----------------------------")
cofe_1 = obj['Melozio']
print(cofe_1['price'])

    

#for objects, objects_info in obj.items():
    #Вывод всех типов кофе с атрибутами
    #print(f"\nObjects: {objects_info}")
    # desc = f"{objects_info['description']}{objects_info['price']}"
    # bye_val = objects_info['bye']
    # print(f"\tDescription and price: {desc.title()}")
    # print(f"\tBye: {bye_val.title()}")


# show values
# print(str(obj["orders"][0]["toppings"]))
# print(str(obj["orders"]["size"]))

# for order in obj["orders"]:
#     print(orders)
# print("client name: " + str(obj['client.name']))
# print("gbp: " + str(obj['gbp']))