#include <stdio.h>

#include <bpfinst/native.h>

#include "inst-common.h"

uint64_t arg1, arg2;

volatile uint64_t acc;

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  acc += arg1 + arg2;
  return 0;
}
