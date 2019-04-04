const path = require('path');

const dir      = '/home/tanacchi';
const filename = 'my_file.js';
const suffix   = '.js';

const my_path = path.join(dir, filename);
console.log(my_path);
console.log(path.basename(my_path));
console.log(path.basename(my_path, suffix));

console.log(path.posix.join(dir, filename));
console.log(path.win32.join(dir, filename));
