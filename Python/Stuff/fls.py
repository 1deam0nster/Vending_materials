from flask import Flask, render_template, request
import serial
import time

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/result',methods = ['POST', 'GET'])
def result():
   if request.method == 'POST':
      result = request.form
      print(result)
      return render_template("result.html",result = result)

@app.route('/SomeFunction')
def SomeFunction():

    ser = serial.Serial('COM12', 9600)  
    print(ser.name)   
    time.sleep(2)

    ser.write(b'L1 \n')
    time.sleep(2)

    ser.write(b'L2 \n')
    time.sleep(1)

    ser.write(b'g0 x100\n')

    time.sleep(1)

    ser.write(b'S0 D100\n')

    ser.write(b'S0 D10\n')
    time.sleep(1)

    ser.close()
    print('In SomeFunction')
    return "Nothing"



if __name__ == '__main__':
   app.run()