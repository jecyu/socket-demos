const express = require('express')

const app = express()

app.get('/', function (req, res) {
  res.setHeader('Connection', 'keep-alive')
  res.setHeader('Keep-alive', 'timeout=10')
  res.end('hello world');
})

app.listen(4000)