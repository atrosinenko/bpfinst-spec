#include <stdio.h>

#include <bpfinst/native.h>

#include "../lib/trivial-tag-storage.inc.c"
#include "inst-common.h"

uint64_t ptr;
uint64_t ptr_tag;
uint64_t value;
uint64_t tag;

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  switch (funct) {
  case 1:
    return get_tag(ptr);
  case 2:
    set_tag(ptr, tag);
    if (value > 0 && value % 1001 == 0) {
      fprintf(stderr, "LOAD: value = %lu tag = %lu\n", (long)value, (long)ptr_tag);
    }
    break;
  case 3:
    fprintf(stderr, "SET TAG: %d\n", (int)value);
    break;
  }
  return 0;
}
