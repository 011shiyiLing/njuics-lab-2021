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
         "movl $0,-8(%rbp);"
         "movl $0,-4(%rbp);"
         "jmp .L2;"
    ".L1: movl -4(%rbp),%eax;"
         "movq %rdi,%rdx;"
         "movl %eax,%ecx;"
         "shrq %cl,%rdx;"
         "andl $1,%edx;"
         "testq %rdx,%rdx;"
         "je .L3;"
         "addl $1,-8(%rbp);"
    ".L3: addl $1,-4(%rbp);"
    ".L2: cmpl $63,-4(%rbp);"
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
    "movq %rsp,%rax;"//save PC we are returning now
    "movq %rax,56(%rdi);"
    "xorl %eax,%eax;"
    "retq;"
  );
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
 //longjmp(env, val);
 asm volatile(
  "movq 48(%rdi),%r8;"
  "movq 8(%rdi),%r9;"
  "movq 56(%rdi),%rdx;"

  "movq (%rdi),%rbx;"
  "movq 16(%rdi),%r12;"
  "movq 24(%rdi),%r13;"
  "movq 32(%rdi),%r14;"
  "movq 40(%rdi),%r15;"
  "movl %esi,%eax;"
  "movq %r8,%rsp;"
  "movq %r9,%rbp;"
  "jmpq *%rdx;"
 );
}


