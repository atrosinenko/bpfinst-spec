#include <stdio.h>

#include <bpfinst/native.h>

#include "inst-common.h"

uint64_t value;
uint32_t size;

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  const char *cmd = "NONE";
  if (funct == 1) {
    cmd = "LOAD";
  } else if (funct == 2) {
    cmd = "STORE";
  }

  if (value > 0 && value % 1001 == 0) {
    fprintf(stderr, "%s: value = %lu size = %d\n", cmd, (long)value, size);
  }

  return 0;
}
