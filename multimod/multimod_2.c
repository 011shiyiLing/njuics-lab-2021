#include <stdint.h>

static int i;
static uint64_t arr[1000];


uint64_t modd(uint64_t a,uint64_t b)
{
  if (b > a) return a;
  else if (b==a) return 0;

  else if((b << 4) <= b)//out of bound
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
    res = x & (m-1);
    return res;
  }
  
  else
  {
    res = modd(x,m);
    return res;
  }
  
}

//把a转换成二进制字符数组
void turn_binary(uint64_t a)
{
  uint64_t temp;
  while(a != 0)
  {
    temp = a & 1;
    a = a>>1;
    arr[i] = temp;
    i++;
  }

}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
  uint64_t x=0;
  i =0;
  turn_binary(a);
  for(int j=i-1;j>=0;j--)
  {
    if(arr[j] == 1)
    {
      x += b<<j;
    }
  }
  
  uint64_t res = 0;
  res = mod(x,m);
  return res; 
}

#include <stdint.h>
#include <stdio.h>

uint64_t modd(uint64_t a,uint64_t b)
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
    res = modd(x,m);
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
