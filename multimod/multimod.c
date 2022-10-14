#include <stdint.h>
//#include <stdio.h>

//2^64-1
static uint64_t maxmum = -1;
//2^63
static uint64_t smaxmum = (uint64_t) 1<<63;

uint64_t modd(uint64_t a,uint64_t m)
{
  uint64_t c = m;
  while(a >= m)
  {
    while(c < smaxmum && c < a)
    {
      c = c << 1;
    }
    while(c > a && c > m)
    {
      c = c >> 1;
    }
    a = a - c;
  }  
  return a;
}

//mod operation
uint64_t mod(uint64_t x,uint64_t m)
{
  uint64_t res=0;
  if((m & (m-1)) == 0)//要求m必须是2的正整数幂次
  {
    res = x & (m-1);
    //res = modd(x,m);
    return res;
  }
  
  else
  {
    res = modd(x,m);
    return res;
  }
  
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
  uint64_t exp = mod(a,m);
  uint64_t res = 0;

  while(b)
  {
    if(b&1)//judge b's lasted position == 1
    {
      res = res + exp;
      if(res >= m)
      {
        res = res - m;
      }
    }
    exp = exp << 1;
    if(exp > m)
    {
      exp = exp -m;
    }
    b >>= 1;
  }
  return res;
}

