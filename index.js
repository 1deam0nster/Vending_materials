const express = require('express');
const app = express();
const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));
const SerialPort = require('serialport')
const port = new SerialPort('COM12', {
    baudRate: 9600
  });

const button = (function(_this) {
    return function() {
      lightOn = true;
      return console.log('test');
    };
  })(this);


app.get('/', function(req, res){
   res.send("Hello world!");
   return res.sendFile('index.htm');
});

app.get('/on', function(req, res) {
    clearInterval(interval);
    button();
    return res.end();
  });

  app.get('/off', function(req, res) {
    clearInterval(interval);
    turnOff();
    return res.end();
  });

console.log("Starting...");

port.on('open', function() {

    port.on('data', function (data) {
      console.log(data.toString())
    })
    
    sleep(3000).then(() => {
      let gcode = 'g0 x10\n'
      port.write(gcode.toString(), function(err) {
          if (err) {
            return console.log('Error on write: ', err.message)
          }
          console.log('message written')
        })

    });
   
})

app.listen(3000);