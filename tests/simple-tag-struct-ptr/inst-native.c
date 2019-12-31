#include <stdio.h>

#include <bpfinst/native.h>

#include "../lib/trivial-tag-storage.inc.c"
#include "inst-common.h"

uint64_t ptr, ptr_tag;
uint64_t tag, value;

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  switch (funct) {
  case 1:
    return get_tag(ptr);
  case 2:
    set_tag(ptr, tag);
    break;
  case 3:
    if (tag != 0) {
      fprintf(stderr, "TAG = %d\n", (int)tag);
    }
    break;
  }
  return 0;
}
