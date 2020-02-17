#include <bpfinst/bpf.h>

#include "inst-common.h"

static uint64_t value_addr;

void inst_load(uint64_t addr, int64_t offset)
{
  ptr = addr + offset;
  ptr_tag = tag1();

  if (addr + offset == value_addr) {
    set_tag(*(uint64_t*)value_addr);
  } else {
    set_tag(slow_call(1));
  }
}

void inst_store(uint64_t addr, int64_t offset, uint64_t stored_value)
{
  ptr = addr + offset;
  ptr_tag = tag1();
  value = stored_value;
  tag = tag3();

  slow_call(2);

  if (stored_value == 100501)
    value_addr = addr + offset;
}

void inst_add(uint64_t a, uint64_t b)
{
  if (tag1())
    set_tag(tag1() + b * 3);
  else if (tag2())
    set_tag(a * 3 + tag2());
}

void inst_sub(uint64_t a, uint64_t b)
{
  tag = tag1() - tag2();
  slow_call(3);
}
