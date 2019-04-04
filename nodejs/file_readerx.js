const fs = require('fs');
const data = fs.readFileSync('./fileio.js', (readFileErr, data) => {
  if (readFileErr) throw err;
  console.log(data);
});
console.log(data);
