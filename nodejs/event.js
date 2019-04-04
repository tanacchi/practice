const {EventEmitter} = require('events');
const ev = new EventEmitter();

ev.on('hello', (name) => {
  console.log(`Hello, ${name}`);
});

ev.once('bye', (name) => {
  console.log(`Bye, ${name}`);
});

console.log(ev.eventNames());

ev.emit('hello', 'tanaka');
ev.emit('hello', 'daiki');

ev.emit('bye', 'tanaka');
ev.emit('bye', 'daiki');
