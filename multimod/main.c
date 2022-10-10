#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint32_t multimod(uint32_t, uint32_t, uint32_t);

void test(uint32_t a, uint32_t b, uint32_t m) {
  #define U64 "%" PRIu64
  printf(U64 " * " U64 " mod " U64 " = " U64 "\n", a, b, m, multimod(a, b, m));
}

int main() {
  test(123, 456, 789);
  test(123, 456, -1ULL);
  test(-2ULL, -2ULL, -1ULL); // should be 1
}
