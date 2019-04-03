const http = require('http');
const server = http.createServer((req, res) => {
  res.write("Hello, World!");
  res.end();
}).listen(3000);

// access to http://localhost:3000
