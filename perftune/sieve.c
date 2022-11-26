#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000
#define E 1e-10

static bool is_prime[N];
static int  primes[N];

double Abs(double a,double b)
{
  if(a - b < 0) return b-a;
  return a-b;
}
double Sqrt(double val)
{
  double i,last=0,cur=0;
  for(i=0;i*i<val;i++);
  i--;
  do{
    last = cur;
    i = (val/i+i)/2;
    cur = i*i;
  }while(Abs(cur,last) > E);
  return i;
}


int *sieve(int n) { 
  assert(n + 1 < N);
  int m = Sqrt(n+0.5);
  //for (int i = 0; i <= n; i++)
    //is_prime[i] = true;
  memset(is_prime,true,n);

  for (int i = 2; i <= m; i++) {
    for (int j = i + i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }

  int *p = primes;
  for (int i = 2; i <= m; i++)
    if (is_prime[i]) {
      *p++ = i;
    }
  *p = 0;
  return primes;
}
