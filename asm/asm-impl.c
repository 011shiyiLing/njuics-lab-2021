#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  //return a + b;
  asm(
    "lea (%rdi,%rsi,1),%eax;"
    "retq;"
  );
  return 0;
}

int asm_popcnt(uint64_t x) {
  /*int s = 0;
  for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }*/
  asm(
    "pushq %rbp;"
    "movq %rdi,-24(%rbp);"
    "movl $0,-8(%rbp);"
    "movl $0, -4(%rbp);"
    "jmp .L2;"

    ".L1:"
    "movl -4(%rbp),%eax;"
    "movq -24(%rbp),%rdx;"
    "movl %eax,%ecx;"
    "shrq %cl,%rdx;"
    "movq %rdx,%rax;"
    "andl $1,%eax;"
    "testq %rax,%rax;"
    "je .L3;"
    "addl $1,-8(%rbp);"

    ".L2:"
    "cmpl $63,-4(%rbp);"
    "jle .L1;"
    "movl -8(%rbp),%eax;"
    "popq %rbp;"
    "ret;"

    ".L3:"
    "addl $1,-4(%rbp);"
  );
  return 0;
}

/*void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}*/
