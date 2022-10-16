#include <stdint.h>

//2^64-1
static uint64_t maxmum = -1;
//2^63
static uint64_t smaxmum = (uint64_t) 2<<63;

uint64_t modd(uint64_t a,uint64_t m)
{
  uint64_t c = m;
  while(a >= m)
  {
    while(c < smaxmum && c < a)//prentend out of bound error
    {
      c = c << 2;
    }
    while(c > a && c > m)
    {
      c = c >> 2;
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
    return res;
  }
  
  else
  {
    res = modd(x,m);
    return res;
  }
}

uint64_t plusmod(uint64_t a,uint64_t b,uint64_t m)
{
  uint64_t sum = 0;
  a = mod(a,m);
  b = mod(b,m);
  sum = a+b;
  
  //"a+b" out of bound
  if(a!= 0 && b!=0 && (a-1) >= (maxmum-b))
  {
    sum =  mod(sum,m) + mod(maxmum,m) + mod(1,m);
  }

  return mod(sum,m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
  uint64_t res = 0;
  for(int i=0;i<64;i++)
  {
    if(((a>>i)&1) == 1)
    {
      uint64_t b1 = b;
      for(int j=0;j<i;j++)
      {
        b1 = plusmod(b1,b1,m);
      }

      res = plusmod(res,b1,m);
    }
  } 
  return res;
}

