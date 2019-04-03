const http = require('http');
let server = http.createServer((req, res) => {
  console.log(`URL: ${req.url}`);
  console.log(`Method: ${req.method}`);
  res.end();
}).listen(8080);
// access to http://localhost:8080
