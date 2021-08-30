
    var SerialPort, app, express, fs, interval, lightOn, port, serial, toggle, turnOff, turnOn;
  
    SerialPort = require('serialport').SerialPort;
  
    fs = require('fs');
  
    port = 'COM12';
  
    express = require('express');
  
    serial = null;
  
    interval = null;
  
    lightOn = false;
  
    turnOn = (function(_this) {
      return function() {
        lightOn = true;
        return serial.write(new Buffer([0x01]));
      };
    })(this);
  
    turnOff = (function(_this) {
      return function() {
        lightOn = false;
        return serial.write(new Buffer([0x00]));
      };
    })(this);
  
    toggle = (function(_this) {
      return function() {
        if (lightOn) {
          return turnOff();
        } else {
          return turnOn();
        }
      };
    })(this);
  
    app = express.createServer();
  
    app.get('/', function(req, res) {
      return res.sendfile('index.htm');
    });
  
    app.get('/on', function(req, res) {
      clearInterval(interval);
      turnOn();
      return res.end();
    });
  
    app.get('/off', function(req, res) {
      clearInterval(interval);
      turnOff();
      return res.end();
    });
  
    app.get('/blink', function(req, res) {
      clearInterval(interval);
      interval = setInterval(toggle, 500);
      return res.end();
    });
  
    console.log("Starting...");
  
    fs.stat(port, function(err, stats) {
      if (err != null) {
        console.log("Couldn't stat " + port);
        process.exit();
      }
      console.log("Started.");
      serial = new SerialPort(port, {
        baudrate: 9600
      });
      return app.listen(8080);
    });
  
