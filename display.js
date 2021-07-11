
const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));
const SerialPort = require('serialport')

const port = new SerialPort('/dev/ttyAM0', {
  baudRate: 9600
})

const port_d = new SerialPort('/dev/ttyAM0', {
  baudRate: 9600,
  parser: serialport.parsers.readline("\n")
})




port_d.on("open", function () {
    console.log('open');
    port_d.on('data', function(data) {
        console.log(data);
        if (data == 'G1') {
            alert( "Правильно!" );
            alert( "Вы такой умный!" );
        } else if (data == 'g0') {
            alert( 'Это поздновато' );
        } else {
            alert( 'Верно!' );
        }
    });
});