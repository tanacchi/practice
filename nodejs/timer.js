const immediate = setImmediate(() => {
  console.log("Immediate callback.");  // 2
});
console.log("setImmediate finished.");  // 1

const interval = setInterval(() => {
  console.log("Interval callback.");  // 4, 5, ...
}, 5000);

const timeout = setTimeout(() => {
  console.log("Timeout callback.");  // 3
}, 3000);

// clearImmediate(immediate);
// clearInterval(interval);
// clearTimeout(timeout);
