# from crypt import methods
from flask import Flask, url_for, render_template, request,  redirect, g,  abort
import time, os, subprocess, sys
from serial_commands.commands import connect, open_serial, close, send, read_command, recv, send_command, send_command2, send_command3, sel_turrel, bye_command
import sqlite3 
# from json_bd.bd import read_db
from FDataBase import FDataBase

# Configuration
DATABASE = '/db/data.db'
DEBUG = True
SECRET_KEY = 'fdgfh78@#5?>gfhf89dx,v06k'
UPLOAD_FOLDER = '/static'

app = Flask(__name__, static_folder='static')
app.config.from_object(__name__)
app.config.update(dict(DATABASE=os.path.join(app.root_path,'db/data.db')))
app.config['SEND_FILE_MAX_AGE_DEFAULT'] = 0

### SQL Lite DB functions
#Connect to db
def connect_db():
    conn = sqlite3.connect(app.config['DATABASE'])
    conn.row_factory = sqlite3.Row
    return conn
    
#Run SQL
def create_db():
    db = connect_db()
    with app.open_resource('db/sq_db.sqlite', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()
    db.close()

#Get db
def get_db():
    if not hasattr(g, 'link_db'):
        g.link_db = connect_db()
    return g.link_db

#Close connect to db
@app.teardown_appcontext
def close_db(error):
    if hasattr(g, 'link_db'):
        g.link_db.close()



# Роутинг страниц
@app.route("/index")
@app.route('/')
def index():
    db = get_db()
    dbase = FDataBase(db)
    return render_template('index.html', coffe = dbase.getCoffe())

# @app.route("/index")
# @app.route('/')
# def index():
#     db = get_db()
#     dbase = FDataBase(db)
#     return render_template('index.html', coffe = dbase.getCoffe())

#вариант вызова
@app.route("/index3")
def index3():
    conn = get_db()
    getItems = conn.execute('SELECT * FROM coffe').fetchall()
    conn.close()
    
    print(getItems[0][0]) #id
    print(getItems[0][1]) #name
    print(getItems[0][2]) #description
    print(getItems[0][3]) #short_description
    print(getItems[0][4]) #price
    print(getItems[0][5]) #volume
    print(getItems[0][6]) #g-code
    print(getItems[0][7]) #img_url
    print(getItems[0][8]) #link_url
    print(getItems[0][9]) #flavor
    print(getItems[0][10]) #roasting
    print(getItems[0][11]) #grain
    print(getItems[0][12]) #country
    print(getItems[0][13]) #intensity
    print(getItems[0][14]) #brand
    return render_template('index3.html', coffe = getItems)

#admin routing
@app.route("/admin", methods=["POST", "GET"])
@app.route('/admin/')
def admin():
    db = get_db()
    dbase = FDataBase(db)
    return render_template('admin.html', coffe = dbase.getCoffe(), stuff = dbase.getStuff())

@app.route("/admin/edit_stuff/<int:id_stuff>", methods=["POST", "GET"])
def edit_stuff(id_stuff):
    db = get_db()
    dbase = FDataBase(db)
    if request.method == 'POST':
        res = dbase.updateStuff(id_stuff, request.form['name'], request.form['price'], request.form['value'], request.form['g_code'], request.form['double_price'])
        if not res:
            print('Ошибка обновления')
        else:
            print('БД обновлена успешно')
        return redirect(url_for('admin'))
    elif request.method == 'GET':
        return render_template('edit_stuff.html', items=dbase.getStuffById(id_stuff))

@app.route("/admin/edit/<int:id_coffe>", methods=["POST", "GET"])
def edit_coffe(id_coffe):
    db = get_db()
    dbase = FDataBase(db)
    if request.method == 'POST':
        res = dbase.updateRow(request.form['id'], request.form['name'], request.form['descriptions'], request.form['short_description'], request.form['price'], request.form['value'], request.form['g_code'], request.form['img_url'], request.form['link_url'], request.form['flavor'], request.form['roasting'], request.form['grain'], request.form['country'], request.form['intensity'], request.form['brand'])
        if not res:
            print('Ошибка обновления')
        else:
            print('БД обновлена успешно')
        return redirect(url_for('admin'))
    elif request.method == 'GET':
        return render_template('edit.html', items=dbase.getById(id_coffe))

@app.route('/admin/add_coffe', methods=["POST", "GET"])
def add_coffe():
    db = get_db()
    dbase = FDataBase(db)

    if request.method == 'POST':
        if len(request.form['name']) > 4 and len(request.form['descriptions']) > 15:
            res = dbase.addRow(request.form['id'], request.form['name'], request.form['descriptions'], request.form['short_description'], request.form['price'], request.form['value'], request.form['g_code'], request.form['img_url'], request.form['link_url'], request.form['flavor'], request.form['roasting'], request.form['grain'], request.form['country'], request.form['intensity'], request.form['brand'])
            if not res:
                print('Ошибка добавления res')
            else:
                print('Успешно')
        else:
            print('Ошибка добавления')

    return render_template('add.html', coffe = dbase.getCoffe())


@app.route('/admin/delete/<int:id_coffe>', methods=["POST", "GET"])
def delete(id_coffe):
    db = get_db()
    dbase = FDataBase(db)
    dbase.deleteRow(id_coffe)
    return redirect(url_for('admin'))

@app.route('/upload')  
def upload():  
    return render_template("file_upload_form.html")  
 
@app.route('/success/<int:id_coffe>', methods = ['POST'])  
def success(id_coffe):  
    if request.method == 'POST':  
        print(id_coffe)
        f = request.files['file']  
        f.filename = str(id_coffe) + "_img.png" # name of file
        f.save("static/sort/"+f.filename) 
        return render_template("success.html", name = f.filename)  

@app.route('/admin/control', methods=["POST", "GET"])
def control():
    if request.method == 'POST':
        if request.form['submit_button'] == 'Home':
            send_command('T2')
        if request.form['submit_button'] == 'Drop cap':
            send_command('C0')
        if request.form['submit_button'] == 'Check':
            send_command('C1')
        if request.form['submit_button'] == 'Start':
            send_command('C2')
        if request.form['submit_button'] == 'T1':
            send_command2("T1", request.form['form'])
        if request.form['submit_button'] == 'S0':
            send_command3("S0", request.form['degreed'], request.form['number'])        
        if request.form['submit_button'] == 'Send':
            send_command(request.form['command'])
        return redirect(url_for('control'))
    elif request.method == 'GET':
        return render_template('control.html')



@app.route("/coffe/<int:id_coffe>", methods=['POST', 'GET'])
def showCoffe(id_coffe):
    db = get_db()
    dbase = FDataBase(db)
    item=dbase.getById(id_coffe)
    sugar=dbase.getStuffById(1)
    cream=dbase.getStuffById(2)
    choco=dbase.getStuffById(3)

    if request.method == 'POST':
        # cream = request.form.get('checkbox')
        # sugar = request.form.get('list')
        print(request.form)
        # print(request.form.get('item'))
        # print(request.form.get('sugar'))
        # print(request.form.get('cream'))
        # print(request.form.get('choco'))
        amount = request.form.get('item')
        cream = request.form.get('cream')
        sugar = request.form.get('sugar')
        choco = request.form.get('choco')
        price = item['price']
        total_price = request.form.get('total_price')

        #Записываем -1 или -2 в кол-во
        if amount == 1:
            dbase.incValue(id_coffe, item['value'] - 1)
        if amount == 2:
            dbase.incValue(id_coffe, item['value'] - 2)
        
        # bye_command(amount, total_price, cream, sugar, choco, id_coffe, item['g_code'])
        return render_template('item_bye.html', item=dbase.getById(id_coffe))
    return render_template('item.html', item=item, choco=choco, sugar=sugar, cream=cream  )

@app.errorhandler(404)
def pageNotFount(error):
    return render_template('page404.html', title="Страница не найдена",)


if __name__ == '__main__':
    # app.debug = True
    app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
    app.run(host='127.0.0.1', debug=True)
    # app.run(host='192.168.1.36', debug=True)

