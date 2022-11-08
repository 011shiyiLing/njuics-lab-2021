#include <stdint.h>
#include <stddef.h>

// TODO: replace with your definition
//#include <setjmp.h> // remove this
typedef long long int jmp_buf_t[8];//(x86-64)8个寄存器（RBX、RBP、RSP、R12、R13、R14 、 R15 及PC）的值，就保存在此变量中
struct __jmp_buf_tag
{
    jmp_buf_t __jmpbuf;
};
typedef struct __jmp_buf_tag jmp_buf[1];

#define asm_jmp_buf jmp_buf

int64_t asm_add(int64_t a, int64_t b);
int     asm_popcnt(uint64_t x);
void   *asm_memcpy(void *dest, const void *src, size_t n);
int     asm_setjmp(asm_jmp_buf env);
void    asm_longjmp(asm_jmp_buf env, int val);
