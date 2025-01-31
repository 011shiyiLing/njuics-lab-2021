#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  //return a + b;
  asm volatile(
    "lea (%rdi,%rsi,1),%rax;"
    "retq;"
  );
  return 0;
}

int asm_popcnt(uint64_t x) {
  //for (int i = 0; i < 64; i++) {
    //if ((x >> i) & 1) s++;
  //}
  asm volatile(
         "pushq %rbp;"
         "movq %rsp,%rbp;"
         "movl $0,-8(%rbp);"//s=0
         "movl $0,-4(%rbp);"//i=0
         "jmp .L2;" //no condition jump
    ".L1: movq %rdi,%rdx;"
         "movl -4(%rbp),%ecx;"
         "shrq %ecx,%rdx;"
         "andq $1,%rdx;"
         "cmp $0,%rdx;"
         "je .L3;" //when ZF=0 jump
         "addl $1,-8(%rbp);" //s++
    ".L3: addl $1,-4(%rbp);" //i++
    ".L2: cmpl $63,-4(%rbp);"//i <= 63 ?
         "jle .L1;"
         "movl -8(%rbp),%eax;"
         "popq %rbp;"
         "ret;"
  );
  return 0;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  //return memcpy(dest, src, n);
  asm volatile(
    "shr $2, %2;"
    "cld;" //set DF = 0
    "rep; movsl;"
    "mov %3, %%ecx;"
    "and $3, %%ecx;" //对%cx取余
    "rep; movsb;"
    : //output
    :"D"(dest),"S"(src),"c"(n),"m"(n)//input
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  //return setjmp(env);
  asm volatile(
    "movq %rbx,0(%rdi);"
    "movq %rbp,8(%rdi);"
    "movq %r12,16(%rdi);"
    "movq %r13,24(%rdi);"
    "movq %r14,32(%rdi);"
    "movq %r15,40(%rdi);"
    "leaq 8(%rsp),%rdx;" //save SP as it will be after we return
    "movq %rdx,48(%rdi);"
    "movq (%rsp),%rax;"//save PC we are returning now
    "movq %rax,56(%rdi);"
    "movl $0,%eax;" //置eax为0，即首次调用后，返回值是0
    "ret;"
  );
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
 //longjmp(env, val);
 asm volatile(
  "movq (%rdi),%rbx;"
  "movq 8(%rdi),%rbp;"
  "movq 16(%rdi),%r12;"
  "movq 24(%rdi),%r13;"
  "movq 32(%rdi),%r14;"
  "movq 40(%rdi),%r15;"
  "movq 48(%rdi),%rsp;"
  "movq 56(%rdi),%rdx;"//PC的值存入rdx
  "movl %esi,%eax;"//将val设为setjmp的返回值
  "jmpq *%rdx;"//通过jmp指令实现PC寄存器的加载
 );
}


