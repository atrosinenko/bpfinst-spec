#include <stdio.h>
#include <syscall.h>

#include <bpfinst/native.h>

#include "inst-common.h"

#include "../lib/trivial-tag-storage.inc.c"

uint64_t event_before_syscall(uint32_t num, uint32_t *drop_syscall,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5, uint64_t arg6)
{
  // syscall(10001, &int32)
  if (num == 10001) {
    fprintf(stderr, "TAGGING...\n");
    scanf("%d", (int32_t *)arg1);
    set_tag(arg1, 1);
  }
  // syscall(20002, &int32)
  if (num == 20002) {
    fprintf(stderr, "Result: %d (%s)\n", *(int32_t *)arg1, get_tag(arg1) ? "TAINTED" : "NOT TAINTED");
  }
  return 0;
}

uint64_t event_dispatch_slow_call(uint64_t funct)
{
  int64_t addr = (int64_t)funct;
  if (addr < 0) {
    return get_tag(-addr);
  } else {
    set_tag(addr, 1);
  }
  return 0;
}
