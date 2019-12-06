#include <stdio.h>

#include <bpfinst/native.h>

#include "common.h"
#include "../lib/trivial-tag-storage.inc.c"

uint64_t arg1, arg2;

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  switch (funct) {
  case GET_TAG:
    return get_tag(arg1);
  case SET_TAG:
    set_tag(arg1, arg2);
    break;
  case REPORT:
    fprintf(stderr, "Result: %d\n", (int)arg1);
    break;
  }
  return 0;
}
