#!/bin/sh
# Run command for fastest-primes. Builtins only, no forks: exec the prebuilt
# static binary directly. If it cannot run (wrong arch / missing file),
# fall back to compiling the standalone sieve from source.
d=${0%/*}
[ "$d" = "$0" ] && d=.
if [ -x "$d/primes" ]; then
  exec "$d/primes"
fi
cc -O3 -o /tmp/aiprove_primes "$d/sieve.c" && exec /tmp/aiprove_primes
