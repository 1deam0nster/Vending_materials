var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/servo2', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// router.get('/on:id', function(req, res) {
//   console.log('test');
//   console.log('Username: ' + req.body.username);
//   console.log('Password: ' + req.body.password);  
//   return res.end();
// });



module.exports = router;