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
    "push ebp;"
    "mov ebp,esp;"
    "sub esp,0x40;"
    "push esi;"
    "push ebx;"

    "mov eax,0;"
    "mov ebx,[ebp+8];"

    "mov [ebx],eax;"
    "mov [ebx+4],ecx;"
    "mov [ebx+8],edx;"
    "mov [ebx+12],esi;"
    "mov [ebx+16],edi;"

    "lea esi,[ebp+4];"
    "mov [ebx+20],esi;"

    "mov esi,[ebp];"
    "mov [ebx+24],esi;"

    "mov esi,[ebp+4];"
    "mov [ebx+32],esi;"

    "pop ebx;"
    "pop esi;"
    "mov esp,ebp;"
    "pop ebp;"
    "ret;"
  );
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
 //longjmp(env, val);
 
}


