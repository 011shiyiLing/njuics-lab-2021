#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];
int sqrt(int val)
{
  int n;
  int i;
  int tmp,ttp;

  if(val == 0) return 0;
  n = 0;
  tmp = (val >> 30);
  val <<= 2;
  if(tmp > 1){
    n++;
    tmp -= n;
  }
  for(i=15; i>0; i--)
  {
    n <<= 1;
    tmp <<= 2;
    tmp += (val >> 30);
    ttp = n;
    ttp = (ttp << 1) + 1;
    val <<= 2;
    if(tmp >= ttp)
    {
      tmp -= ttp;
      n++;
    }
  }
  return n;

}

int *sieve(int n) { 
  assert(n + 1 < N);
  int m = sqrt(n+1);
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
