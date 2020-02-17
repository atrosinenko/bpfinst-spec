#include <bpfinst/bpf.h>

#include "inst-common.h"

static uint64_t value_addr, tag_addr;

void inst_load(uint64_t addr, int64_t offset)
{
  ptr = addr + offset;
  ptr_tag = tag1();

  if (addr + offset == value_addr) {
    set_tag(*(uint64_t*)tag_addr);
    slow_call(3);
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
  if (stored_value == 100502)
    tag_addr = addr + offset;
}

// arr_ptr + idx1 * sizeof(...) + idx2 * sizeof(...) + idx3 * sizeof(uint64_t)

void inst_add(uint64_t a, uint64_t b)
{
  set_tag(tag1() + tag2());
}

void inst_mul(uint64_t a, uint64_t b)
{
  set_tag(tag1() * b + a * tag2());
}

void inst_shl(uint64_t a, uint64_t l)
{
  if (l == 3)
    set_tag(a << 3);
}
