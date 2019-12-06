#include <stdio.h>

#include <bpfinst/native.h>

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  fprintf(stderr, "CALL: %lu\n", funct);
  return 123;
}
