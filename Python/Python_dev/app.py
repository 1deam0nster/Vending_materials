from flask import Flask, url_for, render_template, request, json
import time
import serial

app = Flask(__name__)


sugar_x = False
cream_x = False
sugar_y = False
cream_y = False

class Serializer:

    def __init__(self):
        self.ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5, writeTimeout=5)

    def open(self):
        if(self.ser.isOpen() == False):
            self.ser.open()
            print("Serial is open")
        else:
            print("Serial already open")

    def close(self):
        self.ser.close()
        print("Serial is close")

    def send(self, msg):
        self.ser.write(msg)
    
    def read_command(self):
        print("read commands")
        data = self.ser.readline().decode()
        print(data)

    def recv(self):
        return self.ser.readline()





# Роутинг страниц
@app.route('/')
def index():
    return render_template('index.html')


@app.route('/coffe_y/', methods=['POST', 'GET'])
def coffe_y():
    if request.method == 'POST':
        #print(request.form.getlist('mycheckbox'))
        postlist = request.form.getlist('mycheckbox')
        print(postlist)


        if '2' in postlist and len(postlist) == 1:
            print("Сахар")
        if '1' in postlist and len(postlist) == 1:
            print("Сливки")
        if len(postlist) == 2:
            print("Сливки и сахар")
        if len(postlist) == 0:
            print("Кофе")
            print("connect")
            # ard.connect()
            ard.open()
            print("connect ok")
            ard.send(b'x1\n')            
            print("send ok")
            ard.close()
        return render_template('pay_y.html')
    return render_template('coffe_y.html')


@app.route('/coffe_x/')
def coffe_x():
    return render_template('coffe_x.html')


@app.route('/send_coffe_y', methods=['POST'])
def send_coffe_y():
    user =  request.form['username']
    password = request.form['password']
    print(password)
    print(user)
    return json.dumps({'status':'OK','user':user,'pass':password})




if __name__ == '__main__':
    ard = Serializer()
    app.debug = True
    app.run(host='127.0.0.1')
