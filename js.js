
const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));
const SerialPort = require('serialport')
const port = new SerialPort('COM12', {
    baudRate: 9600
  })


// The open event is always emitted
port.on('open', function() {

      port.on('data', function (data) {
        console.log(data.toString())
      })
      
      sleep(3000).then(() => {
        let gcode = 'g0 x100\n'
        port.write(gcode.toString(), function(err) {
            if (err) {
              return console.log('Error on write: ', err.message)
            }
            console.log('message written')
          })

      });
     
})