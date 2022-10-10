#include <stdint.h>

//mod operation
uint32_t mod(uint64_t x,uint64_t m)
{
  uint32_t res;
  res = x & (m-1);
  return res;
}

//multiply operation
uint32_t multiply(uint32_t a,uint32_t b)
{
  uint32_t res =0;
  for(int i=b;i>0;i--)
  {
    res += a;
  }
  return res;
}

uint32_t multimod(uint32_t a, uint32_t b, uint32_t m) {
  uint32_t x;
  x = multiply(a,b); 
  uint32_t res = 0;
  res = mod(x,m);  
  return res; 
}
