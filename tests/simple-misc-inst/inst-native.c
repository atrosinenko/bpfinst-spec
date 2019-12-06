#include <stdio.h>

#include <bpfinst/native.h>

#include "inst-common.h"

uint64_t arg1, arg2;

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  if (arg1 > 0 && arg1 % 1001 == 0) {
    fprintf(stderr, "funct = %lu: %lu %lu\n", (long)funct, (long)arg1, (long)arg2);
  }
  if (arg2 > 0 && arg2 % 1001 == 0) {
    fprintf(stderr, "funct = %lu: %lu %lu\n", (long)funct, (long)arg2, (long)arg1);
  }
  return 0;
}
