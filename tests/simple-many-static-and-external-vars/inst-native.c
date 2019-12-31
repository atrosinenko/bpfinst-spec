#include <stdio.h>

#include <bpfinst/native.h>

#include "inst-common.h"

uint64_t arg1, arg2;
uint64_t args[2];

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  fprintf(stderr, "arg1 = %d arg2 = %d\n", (int)arg1, (int)arg2);
  fprintf(stderr, "args: %d %d\n", (int)args[0], (int)args[1]);
  return 0;
}
