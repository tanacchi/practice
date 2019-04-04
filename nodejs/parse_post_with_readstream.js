const http = require('http');

const server = http.createServer((req, res) => {
  if (req.method != 'POST') {
    res.end();
    return;
  }

  let body = '';
  req.on('data', (chunk) => {
    body += chunk;
  });
  req.on('end', () => {
    console.log(body);
    res.end();
  });
});
server.listen(3000);

// do this
// $ curl -X POST -d 'Hello, World!' http://localhost:3000
