#include <bpfinst/bpf.h>

#include "common.h"

void inst_add(uint64_t a, uint64_t b)
{
  set_tag((tag1() + tag2()) & ~1);
}

void inst_and(uint64_t a, uint64_t b)
{
  if (a == 1023) {
    set_tag(b);
  }
  if (b == 1023) {
    set_tag(a);
  }
}

void inst_sub(uint64_t a, uint64_t b)
{
  if (b == 1023) {
    arg1 = tag1();
    slow_call(REPORT);
  }
}

void inst_load(uint64_t addr, int64_t offset)
{
  arg1 = addr + offset;
  set_tag(slow_call(GET_TAG));
}

void inst_store(uint64_t addr, int64_t offset, uint64_t value)
{
  arg1 = addr + offset;
  arg2 = tag3();
  slow_call(SET_TAG);
}
