const fs = require('fs');
const n = parseInt(fs.readFileSync(0, 'utf8').trim(), 10);
if (n < 2) { console.log(0); process.exit(0); }
const sieve = new Uint8Array(n + 1);
let cnt = 0;
for (let i = 2; i <= n; i++) {
  if (!sieve[i]) { cnt++; if (i * i <= n) for (let j = i * i; j <= n; j += i) sieve[j] = 1; }
}
console.log(cnt);
