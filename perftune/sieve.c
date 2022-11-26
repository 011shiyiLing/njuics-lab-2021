#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];


int *sieve(int n) { 
  assert(n + 1 < N);
  int m = sqrt(n+0.5);
  //for (int i = 0; i <= n; i++)
    //is_prime[i] = true;
  memset(is_prime,true,n);

  for (int i = 2; i <= m; i++) {
    for (int j = i + i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }

  int *p = primes;
  for (int i = 2; i <= n; i++)
    if (is_prime[i]) {
      *p++ = i;
    }
  *p = 0;
  return primes;
}
