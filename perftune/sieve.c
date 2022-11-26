#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static int is_prime[N];
static int  primes[N];

int *sieve(int n) {
  assert(n + 1 < N);
  //for (int i = 0; i <= n; i++)
    //is_prime[i] = true;

  for (int i = 2; i <= n; i++) {
    for (int j = i + i; j <= n; j += i) {
      is_prime[j] = 1;
    }
  }

  int *p = primes;
  for (int i = 2; i <= n; i++)
    if (!is_prime[i]) {
      *p++ = i;
    }
  *p = 0;
  return primes;
}
