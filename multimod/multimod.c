#include <stdint.h>
#include <stdio.h>

//mod operation
uint64_t mod(uint64_t x,uint64_t m)
{
  uint32_t res;
  res = x & (m-1);
  return res;
}

//multiply operation
uint64_t multiply(uint64_t a,uint64_t b)
{
  uint32_t res =0;
  for(int i=b;i>0;i--)
  {
    res += a;
  }
  return res;
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t x=0;
  x = multiply(a,b); 
  printf("%lu\n",x);
  uint64_t res = 0;
  res = mod(x,m);  
  return res; 
}
