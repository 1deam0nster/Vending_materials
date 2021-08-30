let {PythonShell} = require('python-shell')

// var options = {
//   mode: 'text',
//   pythonPath: 'C:\Program Files (x86)\Python39-32\python.exe',
//   pythonOptions: ['-u'], // get print results in real-time
//   scriptPath: './',
// };

PythonShell.run('script.py', function (err, results) {
    if (err) throw err;
    // results is an array consisting of messages collected during execution
    console.log('results: %j', results);
  });