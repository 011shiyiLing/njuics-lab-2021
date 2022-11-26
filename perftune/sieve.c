#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N]={1,1};
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

  for(int i=2;i <= n;i++)
  {
    if(!is_prime[i]) primes[cnt++] = i;
    for(int j=1; primes[j] <= n/i; j++)
    {
      is_prime[primes[j]*i] = true;
      if(i % primes[j] == 0) break;//only mark once
    }
  }
  return primes;
}
