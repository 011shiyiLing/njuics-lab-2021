#include <stdint.h>

static uint64_t arr[64];
static uint64_t i=0;
//2^64-1
static uint64_t maxmum = -1;
//2^63
static uint64_t smaxmum = (uint64_t) 1<<63;

uint64_t bitof(uint64_t a,uint64_t i)
{
  return ((a>>i)&1);
}

uint64_t modd(uint64_t a,uint64_t m)
{
 uint64_t m1 = m;
 while(a >= m)
 {
  while(m1 < smaxmum && m1 < a)
  {
    m1 = m1 << 1;
  }
  while(m1 > a && m1 > m)
  {
    m1 = m1 >> 1;
  }
  a -= m1;
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

void turn_binary(uint64_t t)
{
  uint64_t a = t;
  while(a != 0)
  {
    uint64_t temp = mod(a,2);
    arr[i] = temp;
    a = a >> 1;
    i++;
  }
}

//attention:'a+b''s value is out of bound
//(a+b) mod m = (a mod m + b mod m)mod m
uint64_t plusmod(uint64_t a,uint64_t b,uint64_t m)
{
  uint64_t sum = 0;
  a = mod(a,m);
  b = mod(b,m);

  sum = a+b;

  while(a != 0 && b!= 0  && b-1 >= maxmum - a)
  {
    a = mod(sum,m);
    b = mod(maxmum,m) + mod(1,m);
    sum = a+b;
  }

  uint64_t res = 0;
  res = mod(sum,m);
  return res;
}


uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
  uint64_t x=0;
  turn_binary(a);
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
