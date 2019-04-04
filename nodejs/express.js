const express = require('express');
const server  = express();

server.listen(3000);

server.get('/', (req, res) => {
  res.send('Received with GET method.\n');
});

server.post('/', (req, res) => {
  res.send('Received with POST method.\n');
});
