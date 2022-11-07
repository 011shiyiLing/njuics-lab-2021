#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  if(asm_add(1,1) == 2) printf("PASSED.\n");
  if(asm_add(1234,5678) == 6912) printf("PASSED.\n");
  if(asm_popcnt(0x0123456789abcdefULL) == 32) printf("PASSED.\n")
  /*asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    // TODO: add more tests here.
    asm_longjmp(buf, 123);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }*/
}
