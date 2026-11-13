import subprocess, time, statistics
def bench(cmd, inp, reps=25):
    ts = []
    for _ in range(reps):
        t0 = time.perf_counter()
        p = subprocess.run(cmd, input=inp, capture_output=True)
        ts.append((time.perf_counter() - t0) * 1000)
    return min(ts), statistics.median(ts)
for n, exp in [(1000000, "78498"), (5000000, "348513")]:
    inp = f"{n}\n".encode()
    for name, cmd in [("table-binary ./primes", ["./primes"]),
                      ("C sieve ./sieve", ["./sieve"]),
                      ("node sieve", ["node", "sieve.js"])]:
        lo, med = bench(cmd, inp)
        out = subprocess.run(cmd, input=inp, capture_output=True).stdout.decode().strip()
        print(f"N={n} {name}: min={lo:.2f}ms median={med:.2f}ms out={out} {'OK' if out==exp else 'WRONG!'}")
