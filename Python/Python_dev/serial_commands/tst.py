Dict = {
    'item': '1',
    2 : '2'
}

match Dict:
    case {
    'item': '1',
    2 : '2'
}:
        print("1 coffe")
    case  {'item': '2', _, _, _, _}:
        print("1 coffe")

# Creating a Dictionary
#Dict = {1: 'Geeks', 'name': 'For', 3: 'Geeks'}
# accessing a element using get()
# method
print("Accessing a element using get:")
print(Dict.get(3))