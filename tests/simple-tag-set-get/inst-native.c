#include <stdio.h>

#include <bpfinst/native.h>

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  if (funct == (uint64_t)-1) {
    fprintf(stderr, "SETTING...\n");
  } else if (funct == (uint64_t)-2) {
    fprintf(stderr, "READING...\n");
  } else if (funct != 0) {
    fprintf(stderr, "TAG = %d\n", (int)funct);
  }
  return 0;
}
