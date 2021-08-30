const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));
const SerialPort = require('serialport')
const port_d = new SerialPort('/dev/ttyS1', {
    baudRate: 9600
})



port_d.on("open", function () {
    console.log('open');
    port_d.on('data', function (data) {
        console.log(data.toString());
        let text = data.toString()
        console.log(text)
        if (text == 'g1') {
            console.log("Правильно!");
            console.log("Вы такой умный!");
        } else if (data == 'g1 /n') {
            console.log('Это поздновато');
        } else {
            console.log('Верно!');
        }
    });
});