const http = require('http');
const url  = require('url');

let server = http.createServer((req, res) => {
  let parsedRequest = url.parse(req.url, true);
  console.log(parsedRequest);
  res.end();
}).listen(8080);
