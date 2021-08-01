var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var bodyParser = require('body-parser');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var servoRouter = require('./routes/servo');
var servo2Router = require('./routes/servo2');
var relayRouter = require('./routes/relay');
var buttonsRouter = require('./routes/buttons');

const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));
const SerialPort = require('serialport')
const port = new SerialPort('COM12', {
    baudRate: 9600
  })


var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// app.use(bodyParser.urlencoded());
// create application/json parser
var jsonParser = bodyParser.json()
 
// create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false })

app.post('/', urlencodedParser, function (req, res) {
  res.redirect(req.get('referer'));
  // console.log('G0 X:' + req.body.x + ' Y:' + req.body.y + ' Z:' + req.body.z);
  let gcode = 'g0 X' + req.body.x + ' Y' + req.body.y + ' Z' + req.body.z + '\n';
  port.write(gcode.toString(), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('G0 X:' + req.body.x + ' Y:' + req.body.y + ' Z:' + req.body.z);
  })

})

app.post('/servo', urlencodedParser, function (req, res) {
  res.redirect(req.get('referer'));
  let servo_d = 'S0 D' + req.body.d + '\n';
  port.write(servo_d.toString(), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('S0 D:' + req.body.d);
  })
})

app.post('/servo2', urlencodedParser, function (req, res) {
  res.redirect(req.get('referer'));
  let servo_d = 'S1 D' + req.body.d + '\n';
  port.write(servo_d.toString(), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('S1 D:' + req.body.d);
  })
})

app.post('/relay', urlencodedParser, function (req, res) {
  res.redirect(req.get('referer'));
  let relay_1 = 'G1 \n';
  let relay_2 = 'L2 \n';
  port.write(relay_1.toString(), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('L1');
  })
  port.write(relay_2.toString(), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('L1');
  })
})

app.post('/buttons', urlencodedParser, function (req, res) {
  res.redirect(req.get('referer'));
  // console.log('G0 X:' + req.body.x + ' Y:' + req.body.y + ' Z:' + req.body.z);
  let gcode = 'r1 n' + req.body.n + ' t' + req.body.t + '\n';
  port.write(gcode.toString(), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('R1 N:' + req.body.n + ' T:' + req.body.t);
  })

})

// POST /api/users gets JSON bodies
app.post('/servo', jsonParser, function (req, res) {
  // create user in req.body
})

app.use(logger('dev'));
app.use(express.json());
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/servo', servoRouter)
app.use('/relay', relayRouter)
app.use('/servo2', servo2Router)
app.use('/buttons', buttonsRouter)
// app.use(function (req, res) {
//   res.setHeader('Content-Type', 'text/plain')
//   res.write('you posted:\n')
//   res.end(JSON.stringify(req.body, null, 2))
// })



// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;

//порт по умолчанию 3000