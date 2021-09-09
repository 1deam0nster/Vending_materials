const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));
const SerialPort = require('serialport')
const port_d = new SerialPort('/dev/ttyS0', {
    baudRate: 9600
})


let PythonShell = require('python-shell');

let options = {
  mode: 'text',
  pythonPath: '/usr/bin/python3',
  pythonOptions: ['-u'], // get print results in real-time
  scriptPath: 'home/pi',
};

PythonShell.run('test2.py', options, function (err, results) {
  if (err) throw err;
  // results is an array consisting of messages collected during execution
  console.log('results: %j', results);
});



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

// PythonShell.run('test2.py', function (err) {
//     if (err) throw err;
//     console.log('finished');
// });
