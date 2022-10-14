#include <stdint.h>
#include <stdio.h>

uint64_t moddd(uint64_t a,uint64_t b)
{
  if (b > a) return a;
  else if (b==a) return 0;

  else if((b << 4) <= b)
  {
    //printf("%d\n",1);
    while(a >= b)
    {
      a = a-b;
    }
    return a;
  }

  uint64_t c = b;
  while(a >= b)
  {
    while(c < a)
    {
      c = c << 4;

      if(c<=b)
      {
        
      }

      if (c > a)
      {
        c = c>>4;
        break;
      }
    }
    a = a-c;
    c = b;
  }
  return a;
}

//mod operation
uint64_t mod(uint64_t x,uint64_t m)
{
  uint64_t res=0;
  if((m & (m-1)) == 0)//要求m必须是2的正整数幂次
  {
    //res = x & (m-1);
    res = moddd(x,m);
    return res;
  }
  
  else
  {
    res = moddd(x,m);
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

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
  uint64_t x=0;
  uint64_t j = 1;
  for(;j<64;j++)
  {
    if (bitof(a,j) == 0) continue;
    else
    {
      int k =0;
      uint64_t b1 = b;
      for(;k<j;k++)
      {
        b1 = plusmod(b1,b1,m);
      }

      x = plusmod(x,b1,m);
    }
  }
  
  if(bitof(a,0) == 1)
  {
    x = plusmod(x,b,m);
  }
  return x;
}