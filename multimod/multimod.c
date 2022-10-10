#include <stdint.h>

static int i;
static uint64_t arr[100];

//mod operation
uint64_t modd(uint64_t x,uint64_t m)
{
  uint32_t res=0;
  res = x & (m-1);//要求m必须是2的正整数幂次
  return res;
}


uint64_t mod(uint64_t dividend, uint64_t divisor) 
{
    int64_t divdlen = 100, divslen = 100;
    int64_t divsshift;
    
    if(dividend == 0 || divisor == 0) {
        return 0;
    }

    while((divdlen >= 0) && !((dividend >> divdlen) & 0x1)) 
    {
        divdlen--;
    }
    divdlen += 1;

    while((divslen >= 0) && !((divisor >> divslen) & 0x1)) {
        divslen--;
    }
    divslen += 1;
    
    divsshift = ((divisor << (divdlen - divslen)) > dividend) ? (divdlen - divslen - 1) : (divdlen - divslen);
   
    while (dividend >= (divisor << divsshift))
    {
        dividend -= (divisor << divsshift);

        while(dividend < (divisor << divsshift)) 
        {
            divsshift--;
            if(divsshift < 0) return dividend;
        }
        if(divsshift < 0) return dividend;
    }
    
    return dividend;
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
