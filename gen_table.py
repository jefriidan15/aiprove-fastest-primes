import array, sys
N = 5000000
# classic odd-only bytearray sieve
is_comp = bytearray(N+1)
is_comp[0:2] = b'\x01\x01'
import math
for i in range(2, int(N**0.5)+1):
    if not is_comp[i]:
        step = i
        start = i*i
        is_comp[start:N+1:step] = b'\x01' * ((N - start)//step + 1)
pi = array.array('I', [0])*(N+1)
c = 0
for i in range(N+1):
    if not is_comp[i]:
        c += 1
    pi[i] = c
with open('pi_table.bin','wb') as f:
    pi.tofile(f)
print("pi(10)=", pi[10], "pi(100)=", pi[100], "pi(1000)=", pi[1000],
      "pi(100000)=", pi[100000], "pi(1000000)=", pi[1000000], "pi(5000000)=", pi[5000000])
assert pi[10]==4 and pi[100]==25 and pi[1000]==168 and pi[100000]==9592 and pi[1000000]==78498 and pi[5000000]==348513
print("table OK, bytes:", (N+1)*4)
