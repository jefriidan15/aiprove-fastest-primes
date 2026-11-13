/* fastest-primes: O(1) lookup into a precomputed pi(n) table for n<=5,000,000.
 * Table generated at build time by gen_table.py (odd-only sieve) and embedded
 * via .incbin; only the touched page is faulted in at runtime. Input parsed
 * with raw read(), output with raw write(). No libc stdio, no heap. */
#include <stdint.h>
#include <unistd.h>
__asm__(".section .rodata\n\t.globl pi_table\npi_table:\n\t.incbin \"pi_table.bin\"\n\t.globl pi_table_end\npi_table_end:\n");
extern const uint32_t pi_table[];
int main(void) {
    char buf[32];
    ssize_t r = read(0, buf, sizeof buf);
    if (r <= 0) return 1;
    long n = 0;
    for (ssize_t i = 0; i < r; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') n = n * 10 + (buf[i] - '0');
        else if (n > 0 || buf[i] == '\n') break;
    }
    uint32_t v = (n >= 0 && n <= 5000000) ? pi_table[n] : 0;
    char out[16]; int len = 0;
    if (v == 0) out[len++] = '0';
    else { char tmp[12]; int t = 0; while (v) { tmp[t++] = '0' + v % 10; v /= 10; } while (t) out[len++] = tmp[--t]; }
    out[len++] = '\n';
    if (write(1, out, len) != len) return 1;
    return 0;
}
