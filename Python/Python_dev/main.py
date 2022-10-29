from flask import Flask, url_for, render_template, request, json
import time, os, subprocess
from serial_commands.commands import connect, open_serial, close, send, read_command, recv
from json_bd.bd import read_db


app = Flask(__name__)

sugar_x = False
cream_x = False
sugar_y = False
cream_y = False
    

# Роутинг страниц
@app.route("/index")
@app.route('/')
def index():
    obj = read_db()
    # print( url_for('index') )
    return render_template('index.html', obj = obj)

@app.route('/index2')
def index2():
    obj = read_db()
    return render_template('index2.html', obj = obj)

@app.route('/coffe_1/', methods=['POST', 'GET'])
def coffe_1():
    obj = read_db()
    # coffe_1 = obj
    if request.method == 'POST':
        #print(request.form.getlist('mycheckbox'))
        postlist = request.form.getlist('mycheckbox')
        print(postlist)
        print(request.args)

        if '2' in postlist and len(postlist) == 1:
            print("Сахар")
        if '1' in postlist and len(postlist) == 1:
            print("Сливки")
        if len(postlist) == 2:
            print("Сливки и сахар")
        if len(postlist) == 0:
            print("Кофе")
            print("connect")
            connect()
            print("connect ok")
            open_serial()
            send(b'S0 N7 D90\n')
            send(b'S0 N7 D0\n')
            close()           
            print("send ok")
            
            # Рабочий снипет
            # program = "python aqsi.py"
            # process = subprocess.Popen(["python", "aqsi.py --amount=12"])

            # Второй вариант
            # output = os.system('python aqsi.py --amount=24')
            # if output == str(0):
            #     print("Транзакция не прошла")
            # if output == 1:
            #     print("Транзакция прошла")

        return render_template('pay_1.html')

    return render_template('coffe_1.html', obj = obj)

@app.route('/coffe_2/', methods=['POST', 'GET'])
def coffe_2():
    obj = read_db()
    if request.method == 'POST':
        #print(request.form.getlist('mycheckbox'))
        postlist = request.form.getlist('mycheckbox')
        print(postlist)
        print(request.args)

        if '2' in postlist and len(postlist) == 1:
            print("Сахар")
        if '1' in postlist and len(postlist) == 1:
            print("Сливки")
        if len(postlist) == 2:
            print("Сливки и сахар")
        if len(postlist) == 0:
            print("Кофе")
            print("connect")
            connect()
            print("connect ok")
            open_serial()
            time.sleep(2)
            send(b'R0 N1 T1000\n')
            send(b'S0 N7 D80\n')
            time.sleep(2)
            send(b'S0 N7 D0\n')
            close()           
            print("send ok")
            
            #AQSI Terminal start pay
            # program = "python aqsi.py"
            # process = subprocess.Popen(["python", "aqsi.py --amount=12"])
            #----------
            # output = os.system('python aqsi.py --amount=24')
            # if output == str(0):
            #     print("Транзакция не прошла")
            # if output == 1:
            #     print("Транзакция прошла")


            #Write to json file analitics
            program = "python test_write.py"
            process = subprocess.Popen(["python", "test_write.py"])
        return render_template('pay_2.html')

    return render_template('coffe_2.html', obj = obj)

# @app.route('/coffe_x/')
# def coffe_x():
#     return render_template('coffe_x.html')

@app.route('/coffe_3/', methods=['POST', 'GET'])
def coffe_3():
    obj = read_db()
    if request.method == 'POST':
        print(request.form)
    else:
        return render_template('coffe_3.html', obj = obj)


@app.route('/send_coffe_y', methods=['POST'])
def send_coffe_y():
    user =  request.form['username']
    password = request.form['password']
    print(password)
    print(user)
    return json.dumps({'status':'OK','user':user,'pass':password})


# with app.test_request_context():
#     print( url_for('index') )


if __name__ == '__main__':
    app.debug = True
    app.run(host='127.0.0.1')

