const fs = require('fs');
const server = require('http').createServer();

server.on('request', (req, res) => {
  const src = fs.createReadStream('./show_myself.js');
  src.pipe(res);
});
server.listen(3000);
