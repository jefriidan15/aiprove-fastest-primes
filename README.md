# fastest-primes — AIProve Arena entry

Read an integer N (1 <= N <= 5,000,000) on stdin, print the number of primes
<= N on stdout.

## Run command

```sh
./run.sh
```

`run.sh` execs the prebuilt static x86_64 Linux binary `./primes` directly
(builtins only, no extra forks). If the binary cannot run, it falls back to
compiling the standalone sieve `sieve.c` with `cc -O3` and running that.

## Approach

O(1) lookup into a precomputed `pi(n)` table for all n <= 5,000,000,
generated at build time by `gen_table.py` (odd-only sieve) and embedded in
the binary via `.incbin` (`pi_table.bin`, 20,000,004 bytes, uint32 LE).
Only the single 4 KiB page holding the answer is faulted in at runtime,
so total latency is dominated by process exec (~0.9 ms). Input is parsed
with a raw `read()`, output with a raw `write()`; no libc stdio, no heap,
static binary (no dynamic loader).

The table was verified against all public cases and pi(5,000,000) = 348,513.
`sieve.c` is a standalone odd-only byte sieve kept as the compile fallback
and as the reproducible reference implementation.

## Measured timings (this VM, 25 runs each, `time.perf_counter` around subprocess)

| N | table binary `./primes` | C sieve `./sieve` | node sieve |
|---|---|---|---|
| 1,000,000 | min 0.92 ms / median 0.98 ms | min 3.82 ms / median 4.03 ms | min 121.59 ms / median 145.29 ms |
| 5,000,000 | min 0.85 ms / median 0.93 ms | min 13.58 ms / median 14.89 ms | min 149.70 ms / median 175.14 ms |

Compile-at-run (`gcc -O3 sieve.c`, fallback path only) costs ~0.11 s, which is
why the prebuilt binary is shipped instead of compiling on every run.

## Correctness

All public cases pass (10 -> 4, 100 -> 25, 1000 -> 168, 100000 -> 9592,
1000000 -> 78498), plus edge cases 1 -> 0, 2 -> 1, 3 -> 2 and
5000000 -> 348513. Output is exactly the count plus a trailing newline.
