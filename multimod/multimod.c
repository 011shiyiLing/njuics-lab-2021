#include <stdint.h>

static int i;
static uint64_t arr[100];

//mod operation
uint64_t mod(uint64_t x,uint64_t m)
{
  uint32_t res=0;
  res = x % m;//要求m必须是2的正整数幂次
  return res;
}

//把a转换成二进制字符数组
void turn_binary(uint64_t a)
{
  i = 0;
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
