#include <stdint.h>
#include <stdio.h>

static int i;
static uint64_t arr[100];

uint64_t modd(uint64_t a,uint64_t b)
{
  int k = 31;
  //uint64_t res = 0;
  for(;k>=0;k--)
  {
    if((a >> k) >= b)
    {
      a = a & ((1 << k)-1);//取余数继续
      //res += (1 << k);
    }
  }
  return a;//返回最后的余数
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
void turn_binary(uint64_t arr[],uint64_t a,int i)
{
  uint64_t temp;
  while(a != 0)
  {
    temp = mod(a,2);
    a = a>>1;
    arr[i] = temp;
    i++;
  }
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
  //uint64_t arr[100];
  uint64_t x=0;
  i =0;
  turn_binary(arr,a,i);
  for(int j=i-1;j>=0;j--)
  {
    if(arr[j] == 1)
    {
      x += mod(b<<j,m);
    }
  }
  printf("%llu\n",x);
  uint64_t res = 0;
  res = mod(x,m);
  return res; 
}
