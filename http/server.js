const express = require('express')

const app = express()

app.get('/', function (req, res) {
  res.setHeader('Connection', 'close')
  res.end('hello world');
})

app.listen(4000)