/* Standalone fallback: odd-only byte sieve, -O3. Used only if the prebuilt
 * binary cannot run; run.sh compiles this on the spot. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    long n;
    if (scanf("%ld", &n) != 1) return 1;
    if (n < 2) { printf("0\n"); return 0; }
    long m = (n + 1) / 2;
    unsigned char *c = malloc(m);
    memset(c, 0, m);
    for (long i = 3; i * i <= n; i += 2) {
        if (!c[i / 2]) {
            for (long j = i * i; j <= n; j += 2 * i) c[j / 2] = 1;
        }
    }
    long cnt = 1;
    for (long i = 3; i <= n; i += 2) if (!c[i / 2]) cnt++;
    printf("%ld\n", cnt);
    return 0;
}
