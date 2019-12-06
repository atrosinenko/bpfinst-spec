#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

#include <bpfinst/native.h>

#include "inst-common.h"
#define MAX_TAGS (1 << 20)
#include "../lib/trivial-tag-storage.inc.c"

uint64_t arg1, arg2;

uint64_t event_before_syscall(uint32_t num, uint32_t *drop_syscall,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5, uint64_t arg6)
{
  switch (num) {
  case SYS_read:
  case SYS_pread64:
    for (unsigned i = 0; i < arg3; ++i) {
      set_tag(arg2 + i, 1 << arg1);
    }
    break;
  case SYS_write:
    if (get_tag(arg2)) {
      fprintf(stderr, "TAG: %llx\n", (long long)get_tag(arg2));
    }
  }
  return 0;
}

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  switch (funct) {
  case GET_TAG:
    return get_tag(arg1);
  case SET_TAG:
    set_tag(arg1, arg2);
    break;
  default:
    abort();
  }
  return 0;
}
