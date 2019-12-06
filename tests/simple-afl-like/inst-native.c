#include <stdio.h>

#include <bpfinst/native.h>

#include "inst-common.h"

uint32_t afl_map[1 << 16];

void __attribute__((destructor)) destr(void)
{
  int count = 0;
  int footprint = 0;
  for (int i = 0; i < sizeof(afl_map) / sizeof(afl_map[0]); ++i) {
	count += afl_map[i];
    footprint += afl_map[i] > 0;
  }
  printf("Count = %d\n", count);
  printf("Footprint = %d\n", footprint);
  fprintf(stderr, "Count > 0? %s\n",     count > 0     ? "YES" : "NO");
  fprintf(stderr, "Count > 100? %s\n",   count > 100   ? "YES" : "NO");
  fprintf(stderr, "Count > 10000? %s\n", count > 10000 ? "YES" : "NO");
}
