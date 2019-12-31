#include <bpfinst/bpf.h>

#include "inst-common.h"

static uint64_t x, y;
static uint64_t z[2];

void inst_sub(uint64_t a, uint64_t b)
{
  if (b == 123) {
    x = a;
  }
  if (b == 321) {
    z[0] = a;
  }
}

void inst_sdiv(uint64_t a, uint64_t b)
{
  if (b == 123) {
    y = a;
  }
  if (b == 321) {
    z[1] = a;
  }
}

void inst_mul(uint64_t a, uint64_t b)
{
  if (a == 321 || b == 321) {
    arg1 = x;
    arg2 = y;
    args[0] = z[0];
    args[1] = z[1];
    slow_call(0);
  }
}
