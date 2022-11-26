#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static int is_prime[N];
static int  primes[N],cnt;



int *sieve(int n) { 
  //assert(n + 1 < N);
  //for (int i = 0; i <= n; i++)
    //is_prime[i] = true;
  //memset(is_prime,true,n);

  /*for (int i = 2; i <= n/i; i++) {
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
  return primes;*/
  memset(is_prime,1,sizeof(is_prime));
  is_prime[0] = is_prime[1];
  is_prime[2] = 1;
  primes[cnt++] = 2;
  for(int i=3;i <= n;i += 2)
  {
    if(is_prime[i]) primes[cnt++] = i;
    for(int j=1; primes[j] * i <= n && j <= cnt; j++)
    {
      is_prime[primes[j]*i] = 0;
      if(i % primes[j] == 0) break;//only mark once
    }
  }
  return primes;
}
